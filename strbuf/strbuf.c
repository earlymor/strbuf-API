
void strbuf_init(struct strbuf *sb, size_t alloc){
    sb->buf=malloc(sizeof(char)*alloc);
    sb->alloc=alloc;
}
void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc){
    sb->buf=realloc(sb->buf,alloc);
    sb->len=len;
    strcpy(sb->buf,str);
}
void strbuf_release(struct strbuf *sb){
    free(sb->buf);
}

void strbuf_swap(struct strbuf *a, struct strbuf *b){
    int tem;
    char *str;
    //交换字符串
    str=realloc(str,a->alloc);//给临时变量str开辟空间
    strcpy(str,a->buf);//str=a
    a->buf=realloc(a->buf,b->alloc);//重新为a开辟一个与b相同大小的内存空间
    strcpy(a->buf,b->buf);//a=b
    b->buf=realloc(b->buf,a->alloc);//重新为b开辟一个与a相同大小的内存空间
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
    char *str=malloc(*sz);
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
    sb->buf=realloc(sb->buf,0);
    sb->alloc=0;
    strbuf_setlen(sb,0);
}


void strbuf_grow(struct strbuf *sb, size_t extra);//确保在 len 之后 strbuf 中至少有 extra 个字节的空闲空间可用

void strbuf_add(struct strbuf *sb, const void *data, size_t len);//向 sb 追加长度为 len 的数据 data

void strbuf_addch(struct strbuf *sb, int c);//向 sb 追加一个字符 c

void strbuf_addstr(struct strbuf *sb,const char *s){//向 sb 追加一个字符串 s
    if(strlen(s)+sb->len<sb->alloc){//如果缓冲区的容量足够容纳追加字符
        strcpy(sb->buf+sb->len,s);//追加字符串
        sb->len=strlen(sb->buf);//长度
    }

    else {//如果缓冲区容量不够容纳追加字符
        sb->buf=realloc(sb->buf,sb->len+strlen(s)+1);//使用realloc扩充内存空间为缓冲区字符串长度
                                                                 //加上追加字符长度
        strcpy(sb->buf+sb->len,s);//追加字符串
    }
    strbuf_setlen(sb,sb->len+strlen(s));
}

void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2);//向一个 sb 追加另一个 strbuf的数据

void strbuf_setlen(struct strbuf *sb, size_t len){//设置 sb 的长度 len
    sb->len=strlen(sb->buf);                    
}

size_t strbuf_avail(const struct strbuf *sb);//计算 sb 目前仍可以向后追加的字符串长度

void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len);//向 sb 内存坐标为 pos 位置插入长度为 len 的数据 data
