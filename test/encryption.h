#ifndef ENCRYANDDECRY_H
#define ENCRYANDDECRY_H

#define LOG_TAG "inject"
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##args)

#include <unistd.h>
#include <sys/types.h>
#include <android/log.h>
#include <linux/binder.h>
#include <stdio.h>
#include <stdlib.h>
#include <asm/ptrace.h>
#include <asm/user.h>
#include <asm/ptrace.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <dirent.h>
#include <string.h>
#include <jni.h>
#include <android/log.h>
#include <sys/system_properties.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/stat.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
//#include <linux/stat.h>
#include <sys/time.h>
#include <time.h>
/*	缓冲区大小*/
#define BUFFER_SIZE 1024

/*
 * JNI的日志输出
 */


//int gettimeofday(struct timeval *tv, struct timezone *tz);


/*	枚举可选的加密算法	*/
enum crypt {
    Aes_256_ofb, //256位AES算法上述的算法是0.9.7版本,64位输出反馈（OutputFeedback）加密方式
    Aes_192_ofb, //OFB方式的192位AES算法
    Aes_128_ofb, //OFB方式的128位AES算法
    Des_ede3_ofb, //OFB方式的3DES算法，算法的三个密钥都不相同
    Des_ede_ofb, //OFB方式的3DES算法，算法的第一个密钥和最后一个密钥相同，事实上就只需要两个密钥
    Rc2_ofb, //OFB方式的RC2算法，该算法的密钥长度是可变的，可以通过设置有效密钥长度或有效密钥位来设置参数来改变。缺省的是128位。
    Bf_ofb, //OFB方式的Blowfish算法，该算法的密钥长度是可变的
    Enc_null //该算法不作任何事情，也就是没有进行加密处理
};

typedef struct
{
    char Head[16];
    char Item[32];
    char FileName[256];
    char FileType[16];
    unsigned long FileSize;
    int PaddingSize;
    int MapOffset;
    unsigned char Signature[512];
    unsigned char Options[176];
    /* data */
}Padding;

/*
 * 函数声明
 */
int encrypt_init(EVP_CIPHER_CTX *ctx,const char* ockey,const char* alg);
int encrypt_abstract(const char *plaintext_path, EVP_CIPHER_CTX *ctx,
        const char *ciphertext_path);
int decrypt_init(EVP_CIPHER_CTX *ctx,const char * ockey,const char* alg);
int decrypt_abstract(const char *plaintext_path, EVP_CIPHER_CTX *ctx,
        const char *ciphertext_path);
char *get_key(int key_length);
enum crypt get_crypt_config(const char *config_name);
char* create_tmpfile(const char* path);
char* recover_tmpfile(const char* path);
int check_path(const char* path);
int add_head(FILE* file_stream,const char *filepath);
int padding_init(Padding *padding);
int add_padding(FILE* file_stream,Padding *padding);
int get_padding(Padding *padding,const char* filename);
void print_Head(Padding padding);
int get_padding_from_file(FILE* file_stream,Padding *padding);
#endif // ENCRYANDDECRY_H


/*
int main(int argc,char *argv[]) {

    EVP_CIPHER_CTX ctx,de;

    const char* from_path =
            "plaintext.txt"; //明文路径
    const char * to_path = "en.txt";
     const char * de_path = "de.txt";
    const char* enkey ="123456789";
    const char* dekey ="123456789";

    const char* alg ="Des_ede3_ofb";


    encrypt_init(&ctx,enkey,alg);
    encrypt_abstract(from_path, &ctx, to_path);


    decrypt_init(&de,dekey,alg);
    decrypt_abstract(de_path, &de, to_path);



}
*/

///////下面是密钥管理调用加密密钥的函数声明
int base64_encode(unsigned char* in,int inl,unsigned char*out);
int base64_decode(unsigned char* out,int outl,unsigned char*de);
int encrypt_base64(unsigned char *key,unsigned char *plaintext,int plaintext_len,unsigned char *out);
int decrypt_base64(unsigned char *key,unsigned char *cipher_text,unsigned char *de);
