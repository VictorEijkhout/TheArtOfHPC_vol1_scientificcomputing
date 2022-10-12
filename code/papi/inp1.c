/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2019
 ****
 ****************************************************************/

�double sum1, sum2, sum3, sum4;
�double temp1, temp2, temp3, temp4;
�
�sum1 = 0.; sum2 = 0.; sum3 = 0.; sum4 = 0.;
�
for (i = 0; I < n; I ++) {
temp1 = *(a + 0) * *(b + 0);
temp2 = *(a + 1) * *(b + 1);
temp3 = *(a + 2) * *(b + 2);
temp4 = *(a + 3) * *(b + 3);
�
sum1 += temp1;
sum2 += temp2;
sum3 += temp3;
sum4 += temp4;
�
a += 4;
b += 4;
}
�
�return sum1 + sum2 + sum3 + sum4;
�
Above function is still not optimized in terms of �temp� registers.
�
sum1 = 0.; sum2 = 0.; sum3 = 0.; sum4 = 0.;
temp1 = 0.; temp2 = 0.; temp3 = 0.; temp4 = 0.;
�
for (i = 0; I < n; I ++) {
�
sum1 += temp1;
temp1 = *(a + 0) * *(b + 0);
�
sum2 += temp2;
temp2 = *(a + 1) * *(b + 1);
�
sum3 += temp3;
temp3 = *(a + 2) * *(b + 2);
�
sum4 += temp4;
� temp4 = *(a + 3) * *(b + 3);
�
a += 4;
b += 4;
}
�
sum1 += temp1;
sum2 += temp2;
sum3 += temp3;
sum4 += temp4;
�
�return sum1 + sum2 + sum3 + sum4;
