#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

float string_to_float(const char *string_value) {
  char *endptr;
  errno = 0;
  float value = strtof(string_value, &endptr);
  if (endptr == string_value) {
    fprintf(stderr, "ERROR: could not convert '%s' to double\n", string_value);
    exit(EXIT_FAILURE);
  }
  if (errno == ERANGE) {
    fprintf(
        stderr,
        "ERROR: conversion of '%s' to double resulted in underflow or overflow",
        string_value);
    exit(EXIT_FAILURE);
  }
  return value;
}

int main(int argc, char *argv[]) {
  float perc, clip;
  int is_perc_set = 0;
  int is_clip_set = 0;
  int is_d1_set = 0;
  int is_f1_set = 0;
  int is_n1_set = 0;
  int is_d2_set = 0;
  int is_f2_set = 0;
  int is_n2_set = 0;

  struct option long_options[] = {{"perc", required_argument, &is_perc_set, 1},
                                  {"clip", required_argument, &is_clip_set, 1},
                                  {"d1", required_argument, &is_d1_set, 1},
                                  {"f1", required_argument, &is_f1_set, 1},
                                  {"n1", required_argument, &is_n1_set, 1},
                                  {"d2", required_argument, &is_d2_set, 1},
                                  {"f2", required_argument, &is_f2_set, 1},
                                  {"n2", required_argument, &is_n2_set, 1},
                                  {0, 0, 0, 0}};

  int c, option_index;
  while (1) {
    c = getopt_long(argc, argv, "", long_options, &option_index);
    if (c == -1) break;
    printf("c: %d\n", c);
    switch (c) {
      case 0:
        printf("option %s ", long_options[option_index].name);
        printf(" with arg %s\n", optarg);
        break;
      default:
        abort();
    }
  }

  // puts("FINAL STATUS");
  // printf("is_perc_set: %d\n", is_perc_set);
  // if (is_perc_set) printf("perc: %f\n", perc);
  // printf("is_clip_set: %d\n", is_clip_set);
  // if (is_clip_set) printf("clip: %f\n", clip);

  // -----
  // XWIGB
  // -----

  // int n1, n2, nz;
  // float *temp;

  // /* get parameters describind 1st dimension sampling */
  // if (!is_n1_set) {
  //   err("Must specify number of samples in the 1st dimension!\n");
  // }

  // /* read binary data to be plotted */
  // nz = n1 * n2;

  // if (is_clip_set) {
  //   perc = 100.0;
  //   temp = ealloc1float(nz);
  // }

  return 0;
}
