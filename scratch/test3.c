#include <errno.h>
#include <getopt.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void err(const char *format, ...) {
  va_list args;
  va_start(args, format);
  int ret = vfprintf(stderr, format, args);
  va_end(args);
  exit(EXIT_FAILURE);
}

float string_to_float(const char *string_value) {
  char *endptr;
  errno = 0;
  float value = strtof(string_value, &endptr);
  if (endptr == string_value) {
    fprintf(stderr, "ERROR: could not convert '%s' to float\n", string_value);
    exit(EXIT_FAILURE);
  }
  if (errno == ERANGE) {
    fprintf(
        stderr,
        "ERROR: conversion of '%s' to float resulted in underflow or overflow",
        string_value);
    exit(EXIT_FAILURE);
  }
  return value;
}

int string_to_int(const char *string_value) {
  char *endptr;
  errno = 0;
  int value = strtol(string_value, &endptr, 10);
  if (endptr == string_value) {
    fprintf(stderr, "ERROR: could not convert '%s' to int\n", string_value);
    exit(EXIT_FAILURE);
  }
  if (errno == ERANGE) {
    fprintf(
        stderr,
        "ERROR: conversion of '%s' to int resulted in underflow or overflow",
        string_value);
    exit(EXIT_FAILURE);
  }
  return value;
}

int main(int argc, char *argv[]) {
  int n1, n2, nz;
  float perc = 100.0, clip, d1 = 1.0, f1 = 0.0, d2, f2;

  int is_perc_set = 0;
  int is_clip_set = 0;
  int is_d1_set = 0;
  int is_f1_set = 0;
  int is_n1_set = 0;
  int is_d2_set = 0;
  int is_f2_set = 0;
  int is_n2_set = 0;

  struct option long_options[] = {{"perc", required_argument, NULL, 'p'},
                                  {"clip", required_argument, NULL, 'c'},
                                  {"d1", required_argument, NULL, 41},
                                  {"f1", required_argument, NULL, 61},
                                  {"n1", required_argument, NULL, 141},
                                  {"d2", required_argument, NULL, 42},
                                  {"f2", required_argument, NULL, 62},
                                  {"n2", required_argument, NULL, 142},
                                  {0, 0, 0, 0}};

  int c, option_index;
  while (1) {
    c = getopt_long(argc, argv, "p:c:", long_options, &option_index);
    if (c == -1) break;
    switch (c) {
      case 'p':
        is_perc_set = 1;
        perc = string_to_float(optarg);
        break;
      case 'c':
        is_clip_set = 1;
        clip = string_to_float(optarg);
        break;
      case 41:
        is_d1_set = 1;
        d1 = string_to_float(optarg);
        break;
      case 61:
        is_f1_set = 1;
        f1 = string_to_float(optarg);
        break;
      case 141:
        is_n1_set = 1;
        n1 = string_to_int(optarg);
        break;
      case 42:
        is_d2_set = 1;
        d2 = string_to_float(optarg);
        break;
      case 62:
        is_f2_set = 1;
        f2 = string_to_float(optarg);
        break;
      case 142:
        is_n2_set = 1;
        n2 = string_to_int(optarg);
        break;
      default:
        abort();
    }
  }

  // puts("FINAL STATUS");
  printf("is_perc_set: %d\n", is_perc_set);
  if (is_perc_set) printf("perc: %f\n", perc);
  printf("is_clip_set: %d\n", is_clip_set);
  if (is_clip_set) printf("clip: %f\n", clip);
  printf("is_d1_set: %d\n", is_d1_set);
  if (is_d1_set) printf("d1: %f\n", d1);
  printf("is_f1_set: %d\n", is_f1_set);
  if (is_f1_set) printf("f1: %f\n", f1);
  printf("is_n1_set: %d\n", is_n1_set);
  if (is_n1_set) printf("n1: %d\n", n1);

  // -----
  // XWIGB
  // -----

  int iz;
  float *z, *temp;

  /* get parameters describing 1st dimension sampling */
  if (!is_n1_set) err("Must specify number of samples in the 1st dimension!\n");
  // d1 = 1.0;  getparfloat("d1",&d1);
  // f1 = 0.0;  getparfloat("f1",&f1);
  float x1min = (d1 > 0.0) ? f1 : f1 + (n1 - 1) * d1;
  float x1max = (d1 < 0.0) ? f1 : f1 + (n1 - 1) * d1;

  /* read binary data to be plotted */
  nz = n1 * n2;
  z = ealloc1float(nz);

  /* if necessary, determine clip from percentile */
  if (!is_clip_set) {
    // perc = 100.0;  getparfloat("perc",&perc);
    temp = ealloc1float(nz);
    for (iz=0; iz < nz; iz++) {
      temp[iz] = fabs(z[iz]);
    }
  }

  return 0;
}
