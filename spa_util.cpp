// Copyright 2012-present Wen-Yun Yang. All rights reserved.

#include "spa_util.h"

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <limits>

#define MAX_DIMENSION 3
#define TINY 1.0e-20

void vector_add(double *x, double *y, double factor, int n) {
  int i;
  for(i = 0; i < n; i++) {
    x[i] += y[i] * factor;
  }
}

void vector_add_to_new(double *z,
                       double *x,
                       double *y,
                       double factor,
                       int n) {
  vector_copy(z, x, n);
  vector_add(z, y, factor, n);
}

void vector_scale(double *x, double factor, int n) {
  int i;
  for(i = 0; i < n; i++) {
    x[i] *= factor;
  }
}

void vector_init(double *x, int n, double v) {
  int i;
  for(i = 0; i < n; i++) {
    x[i] = v;
  }
}

void eye(double *x, int n) {
  int i;
  int j;
  for(i = 0; i < n; i++) {
    for(j = 0; j < n; j++) {
        if (i == j)
            x[i*n + j] = 1.0;
        else
            x[i*n + j] = 0.0;
    }
  }
}

double vector_inner_product(double *x, double *y, int n) {
  double prod = 0.0;
  int i;
  for(i = 0; i < n; i++) {
    prod += x[i] * y[i];
  }

  return prod;
}

void vector_out_product(double *x, double *y, int n) {
  int i, j;
  for(i = 0; i < n; i++) {
    for(j = 0; j < i; j++) {
      x[i * n + j] = y[i] * y[j];
      x[j * n + i] = x[i * n + j];
    }
    x[i * n + i] = y[i] * y[i];
  }
}

void vector_copy(double *x, double *y, int n) {
  memcpy(x, y, sizeof(double)*n);
}

void vector_normalize(double *x, int n) {
  vector_scale(x, 1 / sqrt(vector_inner_product(x, x, n)), n);
}

double vector_std(double *x, int n) {
  int i;
  double m, s;
  
  m = 0;
  for(i = 0; i < n; i++)
    m += x[i];
  
  m /= n;

  s = 0;
  for(i = 0; i < n; i++) {
    s += pow(x[i] - m, 2);
  }

  s = sqrt(s);
  return s;
}

