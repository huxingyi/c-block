/* Copyright (c) 2014, huxingyi@msn.com
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef C_BLOCK_H
#define C_BLOCK_H

#include <assert.h>

#define C_BLOCK_RET_UNHANDLED                -100
#define C_BLOCK_RET_PENDING                  -101
#define C_BLOCK_RET_FINISHED                 -102

struct c_block {
  int (*func)(void *);
  void *ctx;
  int state;
};

#define c_init(_ctx) do {                               \
    (_ctx)->block.func = 0;                             \
    (_ctx)->block.ctx = (_ctx);                         \
    (_ctx)->block.state = 0;                            \
  } while (0)

#define c_begin(_ctx, _func)  {                                   \
  struct c_block *__this_block = &(_ctx)->block;                  \
  int (*__this_func)(void *) = (int (*)(void *))(_func);          \
  switch (((struct c_block *)__this_block)->state) {              \
    case 0:    

#define c_call(_ctx, _func) do {                        \
    int ret;                                            \
    assert((void *)__this_block != (void *)(_ctx));     \
    (_ctx)->block.func = (int (*)(void *))__this_func;  \
    (_ctx)->block.ctx = __this_block;                   \
    (_ctx)->block.state = 0;                            \
    assert(0 == __this_block->state);                   \
    __this_block->state = __LINE__;                     \
    ret = (_func)(_ctx);                                \
    if (C_BLOCK_RET_PENDING == ret) {                   \
      return ret;                                       \
    } else if (C_BLOCK_RET_FINISHED == ret) {           \
    } else {                                            \
      assert(0 && "c_call:invalid return value");       \
    }                                                   \
    case __LINE__: __this_block->state = 0;             \
  } while (0)

#define c_spawn(_ctx, _func, _callback) do {            \
    int ret;                                            \
    (_ctx)->block.func = (int (*)(void *))(_callback);  \
    (_ctx)->block.ctx = (_ctx);                         \
    (_ctx)->block.state = 0;                            \
    ret = (_func)(_ctx);                                \
    if (C_BLOCK_RET_PENDING == ret) {                   \
    } else if (C_BLOCK_RET_FINISHED == ret) {           \
    } else {                                            \
      assert(0 && "c_spawn:invalid return value");      \
    }                                                   \
  } while (0)

#define c_unhandled(_ctx)             C_BLOCK_RET_UNHANDLED
#define c_finished(_ctx)                                               \
   (((struct c_block *)(_ctx))->func(((struct c_block *)(_ctx))->ctx), \
    C_BLOCK_RET_FINISHED)
#define c_pending(_ctx)               C_BLOCK_RET_PENDING
#define c_end()                   \
    }                             \
  }

#define C_INIT          c_init
#define C_BEGIN         c_begin
#define C_CALL          c_call
#define C_SPAWN         c_spawn
#define C_UNHANDLED     c_unhandled
#define C_FINISHED      c_finished
#define C_PENDING       c_pending
#define C_END           c_end

#define cInit           c_init
#define cBegin          c_begin
#define cCall           c_call
#define cSpawn          c_spawn
#define cUnhandled      c_unhandled
#define cFinished       c_finished
#define cPending        c_pending
#define cEnd            c_end

#endif

