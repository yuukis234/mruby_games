/*
** mrb_games.c - Games class
**
** Copyright (c) yuuki 2019
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include "mrb_games.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  char *str;
  int len;
} mrb_games_data;

static const struct mrb_data_type mrb_games_data_type = {
  "mrb_games_data", mrb_free,
};

static mrb_value mrb_games_init(mrb_state *mrb, mrb_value self)
{
  mrb_games_data *data;
  char *str;
  int len;

  data = (mrb_games_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_games_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "s", &str, &len);
  data = (mrb_games_data *)mrb_malloc(mrb, sizeof(mrb_games_data));
  data->str = str;
  data->len = len;
  DATA_PTR(self) = data;

  return self;
}

static mrb_value mrb_games_hello(mrb_state *mrb, mrb_value self)
{
  mrb_games_data *data = DATA_PTR(self);

  return mrb_str_new(mrb, data->str, data->len);
}

static mrb_value mrb_games_hi(mrb_state *mrb, mrb_value self)
{
  return mrb_str_new_cstr(mrb, "hi!!");
}

void test_init(mrb_state *mrb) {
  struct RClass *games;
  games = mrb_define_class(mrb, "Games", mrb->object_class);
  mrb_define_method(mrb, games, "initialize", mrb_games_init, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, games, "hello", mrb_games_hello, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, games, "hi", mrb_games_hi, MRB_ARGS_NONE());
  DONE;
}

void mrb_mruby_games_gem_init(mrb_state *mrb)
{
  test_init(mrb);
  mrb_window_init(mrb);
  mrb_objects_init(mrb);
  mrb_needs_init(mrb);
  mrb_key_bord_init(mrb);
}

void mrb_mruby_games_gem_final(mrb_state *mrb)
{
}
