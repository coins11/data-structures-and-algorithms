/*
 * sort_util.h: sort_util.c で定義されている関数の宣言. これらの
 *              関数を呼び出す場合はインクルードすること.
 */
int compare(int i, int j);
void swap(int a[], unsigned int i, unsigned int j);
void assign(int a[], unsigned int i, int v);
void print_data(int a[], unsigned int n);
void print_stat();
int verify(int a[], unsigned int n);
