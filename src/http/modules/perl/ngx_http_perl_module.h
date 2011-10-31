
/*
 * Copyright (C) Igor Sysoev
 */


#ifndef _NGX_HTTP_PERL_MODULE_H_INCLUDED_
#define _NGX_HTTP_PERL_MODULE_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <nginx.h>

#include <EXTERN.h>
#include <perl.h>


typedef ngx_http_request_t   *nginx;

typedef struct {
    ngx_str_t                 filename;
    ngx_str_t                 redirect_uri;
    ngx_str_t                 redirect_args;

    SV                       *next;

    ngx_uint_t                done;       /* unsigned  done:1; */

    ngx_array_t              *variables;  /* array of ngx_http_perl_var_t */

#if (NGX_HTTP_SSI)
    ngx_http_ssi_ctx_t       *ssi;
#endif
} ngx_http_perl_ctx_t;


typedef struct {
    ngx_uint_t    hash;
    ngx_str_t     name;
    ngx_str_t     value;
} ngx_http_perl_var_t;


extern ngx_module_t  ngx_http_perl_module;


/*
 * workaround for "unused variable `Perl___notused'" warning
 * when building with perl 5.6.1
 */
#ifndef PERL_IMPLICIT_CONTEXT
#undef  dTHXa
#define dTHXa(a)
#endif


extern void boot_DynaLoader(pTHX_ CV* cv);


void ngx_http_perl_handle_request(ngx_http_request_t *r);
void ngx_http_perl_sleep_handler(ngx_http_request_t *r);



typedef struct {
    ngx_int_t   after;
    SV         *repeat;
    SV         *cb;
} ngx_perl_timer_t;

ngx_connection_t *ngx_perl_timer(ngx_int_t after, SV *repeat, SV *cb);
void ngx_perl_timer_clear(ngx_connection_t *c);


#define NGX_PERL_NOOP        0
#define NGX_PERL_READ        1
#define NGX_PERL_WRITE       2
#define NGX_PERL_CONNECT     4
#define NGX_PERL_CLOSE       8

#define NGX_PERL_EOF        -1
#define NGX_PERL_EINVAL      EINVAL
#define NGX_PERL_ENOMEM      ENOMEM
#define NGX_PERL_EBADE       EBADE
#define NGX_PERL_EBADF       EBADF
#define NGX_PERL_ETIMEDOUT   ETIMEDOUT

typedef struct {
    SV  *connect_cb;
} ngx_perl_connection_t;

void ngx_perl_connector(SV *address, SV *port, SV *timeout, SV *cb);
void ngx_perl_close(ngx_connection_t *c);



#endif /* _NGX_HTTP_PERL_MODULE_H_INCLUDED_ */
