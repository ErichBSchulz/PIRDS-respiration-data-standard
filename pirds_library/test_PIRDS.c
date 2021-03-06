/* Copyright Robert L. Read, 2020
Released under MIT License
*/

#include <stdio.h>
#include <string.h>
#include "minunit.h"
#include "PIRDS.h"

int tests_run = 0;


/* Create a Measurement, load it into an buffer and read it back */
static char *test_can_create_Measurement_and_read_back_as_byte_buffer() {

  Measurement m = {
    'M','T',101,'B',3,-10115
  };
  const unsigned BUFF_SIZE = 13;
  uint8_t buff[BUFF_SIZE];
  int err = fill_byte_buffer_measurement(&m,buff,BUFF_SIZE);
  Measurement mp = get_measurement_from_buffer(buff,BUFF_SIZE);
  mu_assert("measurement byte wrong", m.event == mp.event);
  mu_assert("type wrong", m.type == mp.type);
  mu_assert("device location wrong", m.loc == mp.loc);
  mu_assert("time wrong", m.ms == mp.ms);
  mu_assert("value wrong", m.val == mp.val);
  return 0;
}

static char *test_can_create_Measurement_and_read_back_as_JSON() {
  Measurement m = {
    'M','T',101,'B',3,-10115
  };
  const unsigned BUFF_SIZE = 256;
  char buff[BUFF_SIZE];
  int err = fill_JSON_buffer_measurement(&m,buff,BUFF_SIZE);
  mu_assert("buffer problem", err > 0);

  Measurement mp = get_measurement_from_JSON(buff,BUFF_SIZE);

  mu_assert("measurement byte wrong", m.event == mp.event);
  mu_assert("type wrong", m.type == mp.type);
  mu_assert("device type wrong", m.type == mp.type);
  mu_assert("device location wrong", m.loc == mp.loc);
  mu_assert("time wrong", m.ms == mp.ms);
  mu_assert("value wrong", m.val == mp.val);
  return 0;
}

// For debugging...
void render_message(Message* m) {
  fprintf(stderr,"Message:\n" );
  fprintf(stderr,"Event %c\n", m->event);
  fprintf(stderr,"type %c\n", m->type);
  fprintf(stderr,"ms %u \n", m->ms);
  fprintf(stderr,"%u \n", m->b_size);
  fprintf(stderr,"%s\n",m->buff);
}

// For debugging...
void render_measurement(Measurement* m) {
  fprintf(stderr,"Measurement:\n" );
  fprintf(stderr,"Event %c\n", m->event);
  fprintf(stderr,"type %c\n", m->type);
  fprintf(stderr,"loc %u\n", m->loc);
  fprintf(stderr,"loc %u\n", m->num);
  fprintf(stderr,"ms %d\n", m->ms);
  fprintf(stderr,"val %d\n", m->val);
}

static char *test_can_create_Message_and_read_back_as_byte_buffer() {

  Message m = {
    'E','M',4000,18,"Buckminster Fuller"
  };
  const unsigned BUFF_SIZE = 18+7;
  uint8_t buff[BUFF_SIZE];
  int err = fill_byte_buffer_message(&m,buff,BUFF_SIZE);
  Message mp = get_message_from_buffer(buff,BUFF_SIZE);

  mu_assert("message byte wrong", m.event == mp.event);
  mu_assert("type wrong", m.type == mp.type);
  mu_assert("time wrong", m.ms == mp.ms);
  mu_assert("b_size wrong", m.b_size == mp.b_size);
  mu_assert("string wrong", 0 == strcmp(m.buff,mp.buff));
  return 0;
}

static char *test_can_create_Message_and_read_back_as_JSON() {
  Message m = {
    'E','M',4000,18,"Buckminster Fuller"
  };
  const unsigned BUFF_SIZE = 256+7;
  char buff[BUFF_SIZE];
  int err = fill_JSON_buffer_message(&m,buff,BUFF_SIZE);
  mu_assert("buffer problem", err > 0);

  Message mp = get_message_from_JSON(buff,BUFF_SIZE);

  mu_assert("message byte wrong", m.event == mp.event);
  mu_assert("type wrong", m.type == mp.type);
  mu_assert("time wrong", m.ms == mp.ms);
  mu_assert("b_size wrong", m.b_size == mp.b_size);
  mu_assert("string wrong", 0 == strcmp(m.buff,mp.buff));

  return 0;
}


static char * all_tests() {
  mu_run_test(test_can_create_Measurement_and_read_back_as_byte_buffer);
  mu_run_test(test_can_create_Measurement_and_read_back_as_JSON);

  mu_run_test(test_can_create_Message_and_read_back_as_byte_buffer);
  mu_run_test(test_can_create_Message_and_read_back_as_JSON);

  return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);
    return result != 0;
}
