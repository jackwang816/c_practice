#include<stdio.h>
#include<string.h>
#include"pcreTest.h"

#define EMAIL_PATTERN   "^\\w+([\\.-]?\\w+)*@\\w+([\\.-]?\\w+)*(\\.\\w{2,3})+$"

pcre * get_email_re()
{
    const char* error;
    int errOffset = -1;
    static pcre * re = NULL;

    if (re != NULL)
        return re;
    
    re = pcre_compile(EMAIL_PATTERN, 0, &error, &errOffset, NULL);
    if (NULL == re) {
        printf("PCRE compilation failed at offset %d: %s\n", errOffset, error);
    }

    return re;
}

void destroy_re(pcre** re)
{
    if (*re) {
        pcre_free(*re);
        *re = NULL;
    }
}

int main(int argc, char**argv)
{
    const char* emailStr=NULL;
    int ovector[OVECCOUNT];
    pcre* re=NULL;
    int rc, ret=-1;

    if (argc != 2) {
        printf("usage: pcreTest {email address}\n");
        return -1;
    }

    emailStr = argv[1];
    if (NULL == (re = get_email_re())) {
        return -1;
    }
    do {
        rc = pcre_exec(
            re,                  /* the compiled pattern */         
            NULL,                /* no extra data - we didn't study the pattern */
            emailStr,            /* the subject string */
            strlen(emailStr),    /* the length of the subject */ 
            0,                   /* start at offset 0 in the subject */  
            0,                   /* default options */
            ovector,             /* output vector for substring information */     
            OVECCOUNT);          /* number of elements in the output vector */         
        if (rc < 0) {
            switch(rc)
            {
                case PCRE_ERROR_NOMATCH: printf("No match\n"); break;
                /*
                Handle other special cases if you like
                */
                default: printf("Matching error %d\n", rc); break;
            }
            
            ret = -1;
            break;
        }
        printf("\nMatch succeeded at offset %d\n", ovector[0]);
        ret = 0;
    } while(0);
    
    destroy_re(&re);     /* Release memory used for the compiled pattern */
    return ret;
}