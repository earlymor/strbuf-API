#include "strbuf.h"

void strbuf_init(struct strbuf *sb, size_t alloc){
    sb->buf=(char*)malloc(sizeof(char)*alloc);
    sb->alloc=alloc;
}
void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc){
    sb->buf=(char*)realloc(sb->buf,alloc);
    sb->len=len;
    strcpy(sb->buf,(char*) str);
}
void strbuf_release(struct strbuf *sb){
    free(sb->buf);
}

void strbuf_swap(struct strbuf *a, struct strbuf *b){
    int tem;
    //交换字符串
    char *str=(char*)realloc(str,a->alloc);//给临时变量str开辟空间
    strcpy(str,a->buf);//str=a
    a->buf=(char*)realloc(a->buf,b->alloc);//重新为a开辟一个与b相同大小的内存空间
    strcpy(a->buf,b->buf);//a=b
    b->buf=(char*)realloc(b->buf,a->alloc);//重新为b开辟一个与a相同大小的内存空间
    strcpy(b->buf,str);

    //交换长度
    tem=a->len; 
    a->len=b->len;
    b->len=tem;

    //交换容量
    tem=a->alloc;
    a->alloc=b->alloc;
    b->alloc=tem;

}

char *strbuf_detach(struct strbuf *sb, size_t *sz){
    *sz=sb->alloc;
    char *str=(char*)malloc(*sz);
    strcpy(str,sb->buf);
    strbuf_release(sb);
    return str;
}

int strbuf_cmp(const struct strbuf *first, const struct strbuf *second){
    if(strcmp(first->buf,second->buf)>0)return 1;
    else if(strcmp(first->buf,second->buf)==0)return 0;
    else return -1;
}

void strbuf_reset(struct strbuf *sb){
    sb->buf=(char*)realloc(sb->buf,0);
    sb->alloc=0;
    strbuf_setlen(sb,0);
}


void strbuf_grow(struct strbuf *sb, size_t extra){//确保在 len 之后 strbuf 中至少有 extra 个字节的空闲空间可用
    if(sb->len+extra+1>=sb->alloc)sb->buf=(char*)realloc(sb->buf,sb->len+extra+1);
}
void strbuf_add(struct strbuf *sb, const void *data, size_t len){//向 sb 追加长度为 len 的数据 data
    strbuf_addstr(sb,(char*)data);
}
void strbuf_addch(struct strbuf *sb, int c){//向 sb 追加一个字符 c
    if(sb->alloc>=sb->len+2){
        *(sb->buf+sb->len+1)=(char)c;
    }
    else {
        strbuf_grow(sb,1);
        *(sb->buf+sb->len+1)=(char)c;
    }
}
void strbuf_addstr(struct strbuf *sb,const char *s){//向 sb 追加一个字符串 s
    if(strlen(s)+sb->len<sb->alloc){//如果缓冲区的容量足够容纳追加字符
        strcpy(sb->buf+sb->len+1,s);//追加字符串
        sb->len=strlen(sb->buf);//长度
    }

    else {//如果缓冲区容量不够容纳追加字符
        sb->buf=(char*)realloc(sb->buf,sb->len+strlen(s)+1);//使用realloc扩充内存空间为缓冲区字符串长度
        sb->alloc=sb->len+strlen(s)+1;                                                        //加上追加字符长度
        strcpy(sb->buf+sb->len+1,s);//追加字符串
    }
    strbuf_setlen(sb,sb->len+strlen(s));
}

void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2){//向一个 sb 追加另一个 strbuf的数据
    strbuf_addstr(sb,sb2->buf);
    sb->len+=sb2->len;
    
}

void strbuf_setlen(struct strbuf *sb, size_t len){//设置 sb 的长度 len
    sb->len=strlen(sb->buf);                    
}

size_t strbuf_avail(const struct strbuf *sb){//计算 sb 目前仍可以向后追加的字符串长度
    return sb->alloc-sb->len;
}

void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len){//向 sb 内存坐标为 pos 位置插入长度为 len 的数据 data
    char* str=(char*)malloc(sb->alloc);
    strcpy(str,sb->buf+pos);
    strbuf_addstr(sb->buf+pos,(char*)data);
    strbuf_addstr(sb->buf+pos+len+1,str);
}
void strbuf_ltrim(struct strbuf *sb){//去除 sb 缓冲区左端的所有 空格，tab, '\t'
    char* str=(char*)malloc(sb->alloc);
    int i;
    for( i=0;;i++){
        if(*(sb->buf+i)==' '||*(sb->buf+i)=='\t');
        else break;
    }
    strcpy(str,sb->buf+i);
    strcpy(sb->buf,str);
    sb->len=strlen(sb->buf);
}
void strbuf_rtrim(struct strbuf *sb){//去除 sb 缓冲区右端的所有 空格，tab, '\t'
    for(int i=0;i<sb->len;i++){
        if(*(sb->buf-i+sb->len)==' '||*(sb->buf-i+sb->len)=='\t')*(sb->buf-i+sb->len)='\0';
        else break;
    }
}

void strbuf_remove(struct strbuf *sb, size_t pos, size_t len){//删除 sb 缓冲区从 pos 坐标长度为 len 的内容
    for(int i=0;i<len;i++){
        *(sb->buf+pos+i)='\0';
    }
    strcpy(sb->buf,sb->buf+pos+len+1);
}

ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint){//sb 增长 hint ? hint : 8192 大小， 然后将文件描述符为 fd 的所有文件内容追加到 sb 中
    return 1;//？
}
int strbuf_getline(struct strbuf *sb, FILE *fp){//将 将文件句柄为 fp 的一行内容（抛弃换行符）读取到 sb
    return 0;//?
}
struct strbuf **strbuf_split_buf(const char *str, size_t len, int terminator, int max);
bool strbuf_begin_judge(char *target_str, const char *str, int strnlen);
char *strbuf_get_mid_buf(char *target_buf, int begin, int end, int len);
