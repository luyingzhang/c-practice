/*
 * mutex1.c
 * 以下是一個 reader/writer 程式，程式中有一個reader，一個writer，他們共享
 * 一個 buffer，且使用 mutex 來控制這個 buffer 的存取。
 *
 *  Created on: 2012/6/11
 *      Author: http://gis.nchc.org.tw/lsi/Linux_Basic/discuss/look.asp?id=416&ADMIN=1
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char buffer;
int buffer_has_item = 0;
pthread_mutex_t mutex;
struct timespec delay;

void writer_function(void) {
	while (1) {
		pthread_mutex_lock(&mutex);
		if (buffer_has_item == 0) {
			buffer = make_new_item();
			buffer_has_item = 1;
		}
		pthread_mutex_unlock(&mutex);
		pthread_delay_np(&delay);
	}
}

void reader_function(void) {
	while (1) {
		pthread_mutex_lock(&mutex);
		if (buffer_has_item == 1) {
			consume_item(buffer);
			buffer_has_item = 0;
		}
		pthread_mutex_unlock(&mutex);
		pthread_delay_np(&delay);
	}
}

main() {
	pthread_t reader;

	delay.tv_sec = 2;
	delay.tv_nsec = 0;

	pthread_mutex_init(&mutex, pthread_mutexattr_default);
	pthread_create(&reader, pthread_attr_default, (void*) &reader_function, NULL);
	writer_function();
}

/*
 在這個簡單的程式中，我們假設 buffer 的容量只有 1，因此這個 buffer 有兩
 個可能的狀態：『有一筆資料』或『沒有資料』。 writer 首先將 mutex 鎖定，如
 果 mutex 已經被鎖定，則暫停，直到 mutex 被解鎖。然後看看 buffer 是否是空的，
 若buffer 處於『沒有資料』的狀態，writer 產生一筆新的資料，將其放入 buffer
 中。然後將旗標 buffer_has_item 設為 1，讓 reader 可藉此旗標得知 buffer 內有
 一筆資料。最後 writer 將 mutex 解鎖，並休息 2 秒鐘，讓 reader 可藉此一空檔
 取出 buffer 內的資料。這裡使用的 delay跟之前的 delay 有截然不同的意義，如果
 不加上這個 delay 的話，writer 在 unlock mutex 後的下一個指令就是為了產生另
 一筆新的資料，再度 lock mutex。這將造成 reader 沒有機會讀取 buffer 中的資料
 。因此在此處加上一個 delay 看起來是個不錯的主意。

 reader 看起來和 writer 差不多，它首先 lock mutex，然後看看buffer 中是否
 有資料，若有資料則將其取出，然後將 mutex 解鎖，接著 delay 2 秒，讓 writer 有
 機會放入新的資料。在這個例子中，writer 和 reader 就這樣一直的 run 下去，不斷
 的產生/移除 buffer 中的資料。在其他的情況下，我們可能不再需要使用 mutex 了，
 此時可以使用 pthread_mutex_destroy(&mutex); 來釋放 mutex。

 在初始 mutex 的時候，我們使用了 pthread_mutexattr_default 來當作 mutex
 特性。在 OSF/1 中，mutex 特性沒啥用處，所以這樣設就夠了。

 mutex 一般用在解決 race condition 問題，但是 mutex 並不是一個很強的機制
 ，因為他只有兩個狀態：locked 和 unlocked。POSIX 定義的條件變數（condition
 variable）將 mutex 的功能加以延伸，能夠做到讓某一個 thread 能暫停，並等待另
 一個 thread 的信號（signal）。當信號來了，thread 就醒過來，然後將相關的
 mutex lock 起來。這樣的作法可以解決 reader/writer 程式中的 spin-lock 問題。
 附錄 A 中有一個使用 mutex 和 condition variable 做成的一個簡單的 integer
 semaphores。有關 condition variable 的詳細用法可以參考 man page。

 本節提到的函數有：pthread_mutex_init(),
 pthread_mutex_lock(),
 pthread_mutex_unlock(),
 pthread_mutex_destroy().
 */

