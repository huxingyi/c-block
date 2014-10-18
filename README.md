![c-block](https://raw.githubusercontent.com/huxingyi/c-block/master/c-block.png)

Overview
=================
**c-block** are extremely lightweight macros designed for eliminate callback hell, inspired by [Duff's device](http://en.wikipedia.org/wiki/Duff%27s_device) and [Protothreads](http://dunkels.com/adam/pt/about.html).  **c-block** provide sequential flow of control that is similar to the **await** of c#.

_Callback hell style code:_
```c
void stat_cb(uv_fs_t* req) {
  printf("stat result:%d\n", req->result);
  uv_fs_req_cleanup(req);
  free(req);
}

uv_fs_stat(uv_default_loop(), req, "./test.exe", stat_cb);
```

_**c-block** style code:_
```c
int task_clousre(struct task *ctx) {
  c_begin(ctx, task_clousre);
  ctx->u.stat.loop = uv_default_loop();
  ctx->u.stat.path = "./test.exe";
  c_await(&ctx->u.stat, c_fs_stat);
  uv_fs_req_cleanup(&ctx->u.stat.req);
  c_end();
  free(ctx);
  return 0;
}
```
For full version code, see [c-block-uv](https://github.com/huxingyi/c-block-uv)  

Features
=================
- Low cost, each block use only 12 bytes (on 32bit system)  
- No dependences.  
- Support all platforms.  

Warning
=================
- Do not use local variables. Local variables are not preserved across source lines which containing **c-block** codes. Put the variables into the context struct.
- Do not use switch-case between c_begin and c_end. see [Duff's device](http://en.wikipedia.org/wiki/Duff%27s_device).

Examples
=================
- [c-block-uv](https://github.com/huxingyi/c-block-uv)  
- [c-block-mysql](https://github.com/huxingyi/c-block-mysql)  
