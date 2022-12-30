
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stddef.h>
#include<stdlib.h>
 struct strbuf {
  int len;     //当前缓冲区（字符串）长度
  int alloc;   //当前缓冲区（字符串）容量
  char *buf;   //缓冲区（字符串）
};
void strbuf_setlen(struct strbuf *sb, size_t len){//设置 sb 的长度 len
    sb->len=len; 
    *(sb->buf+len)='\0';                   
}
void strbuf_init(struct strbuf *sb, size_t alloc){
    sb->buf=(char*)malloc(alloc);
    sb->len=0;
    sb->alloc=alloc;
}
void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc){
    strbuf_init(sb,alloc);
    sb->len=len;
    memcpy(sb->buf, str,len+1);
}
void strbuf_grow(struct strbuf *sb, size_t extra){//确保在 len 之后 strbuf 中至少有 extra 个字节的空闲空间可用
    if(sb->len+extra+1>=sb->alloc){
        sb->buf=(char*)realloc(sb->buf,sb->len+extra+1);
        sb->alloc=(sb->len+extra+1);
    }
}
void strbuf_add(struct strbuf *sb, const void *data, size_t len){//向 sb 追加长度为 len 的数据 data
    strbuf_grow(sb,len);
    memcpy(sb->buf+sb->len,data,len+1);
    strbuf_setlen(sb,sb->len+len);
}
void strbuf_addstr(struct strbuf *sb,const char *s){//向 sb 追加一个字符串 s
    
        strbuf_grow(sb,strlen(s));//使用realloc扩充内存空间为缓冲区字符串长度                                                       //加上追加字符长度
        strcpy(sb->buf+sb->len,s);//追加字符串
        strbuf_setlen(sb,sb->len+strlen(s));
    
}
void strbuf_ltrim(struct strbuf *sb){//去除 sb 缓冲区左端的所有 空格，tab, '\t'
    char* str=sb->buf;
    int i;
    for( i=0;;i++){
        if(*(sb->buf+i)==' '||*(sb->buf+i)=='\t');
        else break;
    }
    sb->buf=sb->buf+i;
    strbuf_setlen(sb,strlen(sb->buf));
}
void strbuf_rtrim(struct strbuf *sb){//去除 sb 缓冲区右端的所有 空格，tab, '\t'
    if(sb->buf!=NULL){
        for(int i=sb->len-1;i>0;i--){
        if(*(sb->buf+i)==' '||*(sb->buf+i)=='\t')*(sb->buf+i)='\0';
        else break;
    }
    
    }strbuf_setlen(sb,strlen(sb->buf));
}
void strbuf_remove(struct strbuf *sb, size_t pos, size_t len){//删除 sb 缓冲区从 pos 坐标长度为 len 的内容
    for(int i=0;i<len;i++){
        *(sb->buf+pos+i)='\0';
    }
    strcpy(sb->buf+pos,sb->buf+pos+len);
    sb->len=strlen(sb->buf);
}
ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint){
    strbuf_grow(sb,hint);
    FILE *fp = NULL;
    fp = fdopen(fd, "r"); 
    if(fp==NULL){
        return 0;
    }
    fgets(sb->buf+sb->len,hint,fp);
}
int strbuf_getline(struct strbuf *sb, FILE *fp){
    if(fp==NULL){
        return 0;
    }
    char ch;
    while(ch=fgetc(fp),ch!='\n'&&ch!=EOF){
        strbuf_grow(sb,1);
        *(sb->buf+sb->len)=ch;
        strbuf_setlen(sb,sb->len+1);
    }
    return 0;
}
struct strbuf **strbuf_split_buf(const char *str, size_t len, int terminator, int max){
    struct strbuf**result=malloc(sizeof(struct strbuf*)*max+1);
    int cnt=0;
    int l;
    char* start=(char*)str;
    struct strbuf*sb;
    char*end=NULL;
    for(int i=0;cnt<max-1&&end<len+str;i++){
        for(;*start==(char)terminator;start++);
        end=start;
        for(;*end!=(char)terminator;end++);
        sb=malloc(sizeof(struct strbuf));
        l=end-start;
        strbuf_init(sb,1+l);
        strbuf_add(sb,start,(size_t)l);
        strbuf_setlen(sb,l);
        result[cnt]=sb;
        start=end;
        cnt++;
        }
    result[cnt]=NULL;    
    
    
    return result;
}
int main() {
   char string[] = "14 11 12 123";
    struct strbuf **result = strbuf_split_buf(string, strlen(string), ' ', 1024);

    
} 