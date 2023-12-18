#pragma once

// 获取运算符的下标索引
int getIndex(char theta);

// 获取theta1(栈顶)与theta2之间的优先级
char getPriority(const char& theta1, const char& theta2);

// 判断是否为整型字符
bool In(const char& ch);