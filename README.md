**大概实现思路如下：**

#### 编译流程
1. 词法分析
2. 语法分析
3. 语义分析
4. 中间代码生成
5. 优化
6. 目标代码生成

<br/>

#### 正则表达式

- `[0-9]`：匹配所有的单个数字。
- `[a-z]`：匹配所有的小写字母。
- `[A-Z]`：匹配所有的大写字母。
- `.`：匹配任意单个字符。
- `*`：匹配任意多个（包括零个）模式。
- `+`：匹配一个或多个模式。
- `?`：匹配零个或一个模式。
- `^`：如果在表达式开头使用，表示匹配文本的开头位置。如果在方括号内使用，表示匹配方括号内给定字符集以外的字符。
- `|`：用来连接两个匹配项，表示匹配到两个中的任意一个都行。

<br/>

#### 词法分析器 Lex

```cpp
%{
#include <iostream>
int word_count = 0;
%}

%%
[^" "\r\t\n]+  { word_count++; }
"\n" {
    std::cout << "Word count: " << word_count << std::endl;
    word_count = 0;
}
[" "\r\t]+  { /* skip whitespaces */ }
%%

int yywrap(void) {
    return 0;
}

int main() {
    std::cout << "Enter a sentence: " << std::endl;
    yylex();

    return 0;
}
```



开头处的这段代码是定义区，用来导入你需要的 C++ 头文件和定义全局变量。定义区由 `%{` 和 `%}` 包裹起来。

```cpp
%{
#include <iostream>
int word_count = 0;
%}
```



下面这一段是规则区。每一条规则由一个正则表达式和一段代码构成。当正则表达式匹配成功，调用后面的代码。

```cpp
%%
[^" "\r\t\n]+  { word_count++; }
"\n" {
    std::cout << "Word count: " << word_count << std::endl;
    word_count = 0;
}
[" "\r\t]+  { /* skip whitespaces */ }
%%
```



最后这段是主函数，在主函数中调用 `yylex` 可以启动词法分析器。

```cpp
int main() {
    std::cout << "Enter a sentence: " << std::endl;
    yylex();

    return 0;
}
```

<br/>

#### 语法规则

主类中只可以有一个 main 函数，该函数是公开（ public ）且静态的（ static ）。另外需要注意的是，在 MiniJava 的定义中，`System.out.println` 也是一种语句，但是只可以用来打印整型。

```java
class MainClass {
    public static void main(String[] args) {
        System.out.println(42);
    }
}
```



注意类定义中只可以有类变量定义和类函数定义，不支持构造函数。所有的类变量和类函数都必须是公开的（ public ）。

```java
class Rectangle extends Shape {
    public int width;
    public int height;

    public int area() {
        return this.width * this.area;
    }
}
```



MiniJava 中数组的语法形式如下所示，MiniJava 中只支持整型数组。需要注意的是，在 MiniJava 中，函数内的变量声明需要全部在开头完成，且 return 语句只可以出现在函数体的结尾。另外，`.length` 也是一种语法，仅支持获取数组的长度，其余类不可以使用 length 作为类变量。

```java
class MyClass {
    public int test() {
        int[] a;

        a = new int[3];
        a[0] = 10;
        a[1] = 20;
        a[2] = 30;

        return a.length;
    }
}
```



其它规则：

1. 不支持方法重载。
2. 函数 `System.out.println` 只可以打印整数( int )。
3. `length` 方法只适用于整型数组( int[] )。
4. MiniJava 的代码文件仅支持 ASCII 字符集。
5. 多行注释中不可以包含 /* 和 */。
6. 基础类型只有 `int`，`boolean` 和 `int[]`
7. MiniJava 仅支持单文件，所有的类都需要写在一个文件里。
8. 二元运算符只支持 `&&`，`<`，`+`，`-` 和 `*`。

<br/>

#### 词法描述

```cpp
%{
#include <iostream>

void show_token(const std::string& token_type, const std::string& text);
%}

%%
"class" { show_token("CLASS", yytext); }
"public" { show_token("PUBLIC", yytext); }
"static" { show_token("STATIC", yytext); }
"if" { show_token("IF", yytext); }
"else" { show_token("ELSE", yytext); }
"while" { show_token("WHILE", yytext); }
"true" { show_token("TRUE", yytext); }
"false" { show_token("FALSE", yytext); }
"new" { show_token("NEW", yytext); }
"System.out.println" { show_token("SYSTEM.OUT.PRINTLN", yytext); }
";" { show_token("SEMICOLON", yytext); }
"(" { show_token("LEFT_PARENTHESIS", yytext); }
")" { show_token("RIGHT_PARENTHESIS", yytext); }
"[" { show_token("LEFT_BRACKET", yytext); }
"]" { show_token("RIGHT_BRACKET", yytext); }
"{" { show_token("LEFT_BRACE", yytext); }
"}" { show_token("RIGHT_BRACE", yytext); }
"!" { show_token("NOT", yytext); }
"=" { show_token("ASSIGN", yytext); }
"<" { show_token("LESS_THAN", yytext); }
"&&" { show_token("AND", yytext); }
"+" { show_token("ADD", yytext); }
"-" { show_token("SUBTRACT", yytext); }
"*" { show_token("MULTIPLY", yytext); }
"." { show_token("DOT", yytext); }
([a-zA-Z]|"_")([a-zA-Z0-9]|"_")* { show_token("IDENTIFIER", yytext); }
[0-9]+ { show_token("INTEGER", yytext); }
[" "\t\r\n]+ { /* skip whitespaces */ }
"//".*"\n"         { /* skip a piece of single-line comment */ }
"/*"(.|"\n")*"*/" { /* skip multi-line comments */ }
. { std::cerr << "ERROR!!! UNEXPECTED TOKEN: " << yytext << std::endl; }
%%

int yywrap(void) {
    return 1;
}

void show_token(const std::string& token_type, const std::string& text) {
    // print the token
    std::cout << "(" << token_type << ", " << text << ")" << std::endl;
}

int main() {
    yylex();

    return 0;
}
```

<br/>

#### 语法分析器 Yacc

yacc 是一个使用起来非常简单的语法分析器。它会根据给定的语法格式，自动生成可以用于语法解析的 C/C++  代码。通过运行代码，我们可以对输入的代码文本进行解析，遍历抽象语法树。 lex 可以与 yacc 整合起来，共同使用，直接将 lex  生成的标记序列输入给 yacc ，再由 yacc 进行语法解析，非常方便。

......
