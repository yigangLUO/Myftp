// server.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>

void send_cb(evutil_socket_t fd, short what, void *arg);

// 读缓冲区回调
void read_cb(struct bufferevent *bev, void *arg)
{
    char buf[1024] = {0};
    bufferevent_read(bev, buf, sizeof(buf));
    char *p = "我已经收到了你发送的数据!";
    printf("client say: %s\n", buf);
}

// 写缓冲区回调
void write_cb(struct bufferevent *bev, void *arg)
{
    printf("我是写缓冲区的回调函数...您已发送\n");
}

// 事件
void event_cb(struct bufferevent *bev, short events, void *arg)
{
    if (events & BEV_EVENT_EOF)
    {
        printf("connection closed\n");
    }
    else if (events & BEV_EVENT_ERROR)
    {
        printf("some other error\n");
    }

    bufferevent_free(bev);
    printf("buffevent 资源已经被释放...\n");
}


void cb_listener(
    struct evconnlistener *listener,
    evutil_socket_t fd,
    struct sockaddr *addr,
    int len, void *ptr)
{
    printf("connect new client\n");

    struct event_base *base = (struct event_base *)ptr;
    // 通信操作
    // 添加新事件
    struct bufferevent *bev;
    bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

    // 给bufferevent缓冲区设置回调
    bufferevent_setcb(bev, read_cb, write_cb, event_cb, NULL);
    bufferevent_enable(bev, EV_READ);

    // 创建一个事件
    struct event *ev = event_new(base, STDIN_FILENO,
                                 EV_READ | EV_PERSIST,
                                 send_cb, bev);
    event_add(ev, NULL);
}

void send_cb(evutil_socket_t fd, short what, void *arg)
{
    char buf[1024] = {0};
    struct bufferevent *bev = (struct bufferevent *)arg;
    //   printf("请输入要发送的数据: \n");
    read(fd, buf, sizeof(buf));
    bufferevent_write(bev, buf, strlen(buf) + 1);
}

int main(int argc, const char *argv[])
{

    // init server
    struct sockaddr_in serv;
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(atoi(argv[1]));
    serv.sin_addr.s_addr = htonl(INADDR_ANY);

    struct event_base *base;
    base = event_base_new();
    // 创建套接字
    // 绑定
    // 接收连接请求
    struct evconnlistener *listener;
    listener = evconnlistener_new_bind(base, cb_listener, base,
                                       LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE,
                                       36, (struct sockaddr *)&serv, sizeof(serv));

    event_base_dispatch(base);

    evconnlistener_free(listener);
    event_base_free(base);

    return 0;
}