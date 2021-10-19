/*
	Author:Frozencode
*/
#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
typedef long long ll;
typedef pair<ll,ll> pii;
const ll maxn = 500010;
const ll INF = 2147483647;
const double eps = 1e-12;
const double pi = 3.14159265358979323846264338327950288;
string s;
ll flag, tag;
struct Complex{
	double real;
	double img;
	Complex(){ real = 0, img = 0;}
};
struct my_tokens{
	Complex comp;
	string op;
	ll flag; // flag = 1 comp  flag = 2 op
	my_tokens(){
		flag = 0;
	}
};
Complex s_comp[maxn];
string s_op[maxn];
Complex add(Complex x, Complex y){
	Complex z;
	z.real = x.real + y.real;
	z.img = x.img + y.img;
	return z;
}
Complex sub(Complex x, Complex y){
	Complex z;
	z.real = x.real - y.real;
	z.img = x.img - y.img;
	return z;
}
Complex mul(Complex x, Complex y){
	Complex z;
	z.real = x.real * y.real - x.img * y.img;
	z.img = x.real * y.img + x.img * y.real;
	return z;
}
Complex div(Complex x, Complex y){
	Complex z;
	z.real = (x.real * y.real + x.img * y.img) / (y.real * y.real + y.img * y.img);
	z.img = (x.img * y.real - x.real * y.img) / (y.real * y.real + y.img * y.img);
	return z;
}
Complex cjg(Complex x){
	Complex z;
	z.real = x.real;
	z.img = -x.img;
	return z;
}
Complex arg(Complex x){
	Complex z;
	z.real = atan(x.img / x.real);
	if(x.img < 0 && x.real < 0) z.real -= pi;
	if(x.img > 0 && x.real < 0) z.real += pi;
	return z;
}
Complex mod(Complex x){
	Complex z;
	z.real = sqrt(x.real * x.real + x.img * x.img);
	return z;
}
Complex dis(Complex x, Complex y){
	Complex z;
	z.real = sqrt((x.real - y.real) * (x.real - y.real) + (x.img - y.img) * (x.img - y.img));
	return z;
}// $(3+4i,3+4i)
Complex pow_comp(Complex x, ll cnt){
	Complex z;
	z.real = 1;
	if(cnt == 0){
	}
	else if(cnt < 0){
		z = div(z, pow_comp(x, -cnt));
	}
	else{
		z = mul(x, pow_comp(x, cnt - 1));
	}
	return z;
}
ll priority_m(string ch){
	if(ch == "+" || ch == "-") return 0;
	else if(ch == "*" || ch == "/") return 1;
	else if(ch == "^") return 2;
	else if(ch == "%" || ch == "&" || ch == "#" || ch == "$") return 3; // mod arg cjg dis
	else if(ch == "(" || ch == ")" || ch == "|" || ch == "|") return 4;
	else return -1;
}
void print_comp(Complex x){
	if(fabs(x.real - 0) < eps){
		if(fabs(x.img - 0) > eps){ 
			printf("%.6lf", x.img);
			cout << "i";
		}
		else{
			cout << "0";
		}
	}
	else{
		printf("%.6lf", x.real);
		if(x.img > 0){
			cout << "+";
		}
		if(fabs(x.img - 0) > eps){ 
			printf("%.6lf", x.img);
			cout << "i";
		}
	}
	cout << endl;
}
void print_s(string s, ll pos, ll tag){
	ll len = s.length();
	string tem;
	for(int i = 0; i < len; i++){
		if(i == pos){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
			cout << s[i];
			tem = s[i];
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
		}
		else{
			cout << s[i];
		}
	}
	cout << ", ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
	cout << "error: ";
	if(tag == 1){
		cout << tem << "开头不合法\n";
	}
	else if(tag == 2){
		cout << tem << "结尾不合法\n";
	}
	else if(tag == 3){
		cout << tem << "括号不匹配\n";
	}
	else if(tag == 4){
		cout << tem << "作为操作符后继非法\n";
	}
	else if(tag == 5){
		cout << "空格位置非法\n";
	}
	else if(tag == 6){
		cout << tem << "实数后继非法\n";
	}
	else if(tag == 7){
		cout << tem << "作为(的后继非法\n";
	}
	else if(tag == 8){
		cout << tem << "作为)的后继非法\n";
	}
	else if(tag == 9){
		cout << tem << "作为函数前继非法\n";
	}
	else if(tag == 10){
		cout << tem << "后继非法\n";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}
void check(string s, ll &flag, ll &tag){
	ll len = s.length();
	/* 1: begin end check */
	if(s[0] != '(' && s[0] != '-' && s[0] != '|' && s[0] != 'i' && !('0' <= s[0] && s[0] <= '9') && s[0] != 'a' && s[0] != 'c' && s[0] != 'd'){
		flag = 0;
		tag = 1;
		print_s(s, 0, tag);
		return;
	}
	if(s[len - 1] != ')' && s[len - 1] != '|' && s[len - 1] != 'i' && !('0' <= s[len - 1] && s[len - 1] <= '9')){
		flag = 0;
		tag = 2;
		print_s(s, len - 1, tag);
		return;
	}
	ll cnt1 = 0, cnt2 = 0, pos;
	for(int i = 0; i < len - 1; i++){
		if(s[i] == '('){
			cnt1++;
			pos = i;
		}
		if(s[i] == ')') cnt2++;
		if(cnt2 > cnt1){
			flag = 0;
			tag = 3;
			print_s(s, i, tag);
			return;
		} // () check
		if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/'){
			if(s[i + 1] == ')' || s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == '^'){
				flag = 0;
				tag = 4;
				print_s(s, i + 1, tag);
				return;
			}
		} // op check
		if('0' <= s[i] && s[i] <= '9'){
			if(s[i + 1] == '(' || s[i + 1] == '|'){
				flag = 0;
				tag = 6;
				print_s(s, i + 1, tag);
				return;
			}
		}//digit check
		if(s[i] == '('){
			if(s[i + 1] == ')' ||  s[i + 1] == '+' || s[i + 1] == '*' || s[i + 1] == '/'){
				flag = 0;
				tag = 7;
				print_s(s, i + 1, tag);
				return;
			}
		}
		if(s[i] == ')'){
			if(s[i + 1] == '(' || ('0' <= s[i + 1] && s[i + 1] <= '9')){
				flag = 0;
				tag = 8;
				print_s(s, i + 1, tag);
				return;
			}
		}
		if(i && (s[i] == 'a' || s[i] == 'c' || s[i] == 'd') && ('0' <= s[i - 1] && s[i - 1] <= '9')){
			flag = 0;
			tag = 9;
			print_s(s, i - 1, tag);
			return;
		}
		if(s[i] == 'i'){ // i check
			if(s[i + 1] == '(' || s[i + 1] == 'i' || ('0' <= s[i + 1] && s[i + 1] <= '9')){
				flag = 0;
				tag = 10;
				print_s(s, i, tag);
				return;
			}
		}
	}
	if(s[len - 1] == '('){
		cnt1++;
		pos = len - 1;
	}
	if(s[len - 1] == ')') cnt2++;
	if(cnt2 > cnt1){
		flag = 0;
		tag = 3;
		print_s(s, len - 1, tag);
		return;
	} // () check
	if(cnt1 != cnt2){
		flag = 0;
		tag = 3;
		print_s(s, pos, tag);
		return;
	}
}// arg cjg
bool is_digit(string s){return ('0' <= s[0] && s[0] <= '9');}
double St_to_do(string s){
	ll len = s.length();
	bool flag = true;
	for(int i = 0; i < len; i++){
		if(s[i] == '.') flag = false;
	}
	double res = 0, cnt = 1;
	for(int i = 0; i < len; i++) if(s[i] != '.') res = res * 10 + s[i] - '0';
	if(flag){
	}
	else{
		for(int i = 0; i < len; i++){
			if(flag) cnt = cnt * 10;
			if(s[i] == '.') flag = true;
		}
		res = res / cnt;
	}
	return res;
}
void eval(Complex *s, ll &top, string op){
	if(op == "+" || op == "-" || op == "*" || op == "/"){
		Complex x, y, z;
		x = s[top--];
		y = s[top--];
		if(op == "+") z = add(x, y);
		else if(op == "-") z = sub(y, x);
		else if(op == "*") z = mul(x, y);
		else z = div(y, x);
		s[++top] = z;
	}
	else if(op == "^"){
		Complex x, y, z;
		x = s[top--];
		y = s[top--];
		ll cnt = (long long) x.real;
		z = pow_comp(y, cnt);
		s[++top] = z;
	}
	else if(op == "&"){
		Complex x, z;
		x = s[top--];
		z = arg(x);
		s[++top] = z;
	}
	else if(op == "#"){
		Complex x, z;
		x = s[top--];
		z = cjg(x);
		s[++top] = z;
	}
	else if(op == "$"){
		//cout << "???" << endl;
		Complex x, y, z;
		x = s[top--];
		y = s[top--];
		z = dis(x, y);
		s[++top] = z;
	}
	else{
		Complex x, z;
		x = s[top--];
		z = mod(x);
		s[++top] = z;
	}
}
void break_into_token(string s, vector<string> &tokens, vector<my_tokens> &res){
	ll len = s.length();
	for(int i = 0; i < len; i++){
		if(s[i] == '(' || s[i] == ')' || s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^' || s[i] == '|' || s[i] == 'i' || s[i] == ',' || s[i] == 'x'){
			tokens.pb(s.substr(i, 1));
		}
		else if(s[i] == 'a'){
			tokens.pb("&"); //arg
			i += 2;
		}
		else if(s[i] == 'c'){
			tokens.pb("#"); //cjg
			i += 2;
		}
		else if(s[i] == 'd'){
			tokens.pb("$"); //dis
			i += 2;
		}
		else{
			ll tem = i, cnt = 0;
			while(('0' <= s[tem] && s[tem] <= '9') || s[tem] == '.'){
				tem++;
				cnt++;
			}
			tokens.pb(s.substr(i, cnt));
			i += cnt - 1;
		}
	}
	//for(int i = 0; i < tokens.size(); i++) cout << tokens[i] << endl;
	/* deal with tokens*/
	//tokens to my tokens

	ll mod_cnt = 0;
	for(auto it = tokens.begin(); it != tokens.end(); it = next(it)){
		my_tokens tem;
		if(*it == "|") mod_cnt ^= 1;
		if(*it == ",") continue;
		if(*it == "+" || *it == "-" || *it == "*" || *it == "/" || *it == "^" || *it == "&" || *it == "#" || *it == "$" || *it == "|" || *it == "(" || *it == ")" || *it == "x"){
			tem.op = *it;
			tem.flag = 2;
			res.pb(tem);
		}
		else if(*it == "i"){
			tem.flag = 1;
			if(it == tokens.begin() || *prev(it) != "-"){ // case1 i... case2 3i + i
				tem.comp.real = 0;
				tem.comp.img = 1;
			}
			else if(it != tokens.begin()){
				tem.comp.real = 0;
				tem.comp.img = -1;
				res.pop_back();
			}
			my_tokens op;
			op.flag = 2;
			op.op = "*";
			if(it != tokens.begin() && (*prev(it) == ")" || *prev(it) == "|")) res.pb(op);
			res.pb(tem);
		}
		else{ //digital case
			tem.flag = 1;
			tem.comp.real = St_to_do(*it);
			if(it != tokens.begin()){
				if(*prev(it) == "-"){
					if(prev(it) == tokens.begin() || *prev(prev(it)) == "(" || (*prev(prev(it)) == "|" && mod_cnt == 1)){ // deal with '-' to judge if it is negative or a minus symbol
						res.pop_back();
						tem.comp.real *= -1;
					}
				}
			}//-3 + 4i
			if(next(it) != tokens.end()){
				if(*next(it) == "i"){
					tem.comp.img = tem.comp.real;
					tem.comp.real = 0;
					it = next(it);
					res.pb(tem);
				}
				else{
					if(next(next(it)) != tokens.end()){ // 3 + ?
						if(is_digit(*(next(next(it)))) && *(next(it)) != ","){ // 3 + 4 ?
							if(next(next(next(it))) != tokens.end() && *(next(next(next(it)))) == "i"){ //3 + 4i
								tem.comp.img = St_to_do(*(next(next(it))));
								if(*(next(it)) == "-"){
									tem.comp.img = tem.comp.img * -1;
								}
								it = next(next(next(it)));
							}
						}
						else{
							tem.comp.img = 0;
						}
					}
					res.pb(tem);
				}
			}
			else{
				res.pb(tem);
			}
		}
	}
	/* my_tokens is the functional stack */
	/*	
	for(auto it = res.begin(); it != res.end(); it++){
		my_tokens cur = *it;
		if(cur.flag == 1){
			print_comp(cur.comp);
		}
		else{
			cout << cur.op << endl;
		}
	}
	*/
	// shown part above
}
Complex calculator(string s){ 
	vector <string> tokens;
	vector <my_tokens> res;
	break_into_token(s, tokens, res);
	// now it's time for us to evaluate the expression
	// notes that if tokens'flag = 1 it is a number otherwise it is an operator
	ll top_comp = 0, top_op = 0, cnt = 0;
	for(auto it = res.begin(); it != res.end(); it++){
		my_tokens cur = *it;
		if(cur.flag == 1){
			s_comp[++top_comp] = cur.comp;
		}
		else{
			if(cur.op == "("){
				s_op[++top_op] = cur.op;
			}
			else if(cur.op == ")"){
				while(s_op[top_op] != "("){
					eval(s_comp, top_comp, s_op[top_op]);
					top_op--;
				}
				top_op--;
			}
			else if(cur.op == "|"){
				if(!cnt){
					cnt ^= 1;
					s_op[++top_op] = cur.op;
				}
				else{
					cnt ^= 1;
					while(s_op[top_op] != "|"){
						eval(s_comp, top_comp, s_op[top_op]);
						top_op--;
					}
					eval(s_comp, top_comp, s_op[top_op]);
					top_op--;
				}
			}
			else{
				while(top_op && priority_m(s_op[top_op]) >= priority_m(cur.op) && (s_op[top_op] != "(") && (s_op[top_op] != "|")){
					eval(s_comp, top_comp, s_op[top_op]);
					top_op--;
				}
				s_op[++top_op] = cur.op;
			}
		}
		//if(top_comp) print_comp(s_comp[top_comp]);
	}
	//cout << top_op << endl;
	while(top_op){
		eval(s_comp, top_comp, s_op[top_op]);
		top_op--;
	}
	//cout << top_comp << endl;
	return s_comp[1];
}
int main()
{	
	system("chcp 65001");
	system("cls");
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4); 4红色 7白色
	while(1){
		cout << "请输入你要计算的表达式:\n";
		getline(cin, s);
		string cur = s;
		if(s == "quit"){
			break;
		}
		/* extend equation */
		if(s.substr(0, 5) == "f(x)="){
			vector <my_tokens> cur_my_tokens;
			vector <string> cur_string;
			break_into_token(s.substr(5), cur_string, cur_my_tokens);
			Complex a, b, c;
			for(auto it = cur_my_tokens.begin(); it != cur_my_tokens.end(); it = next(it)){
				my_tokens cur = *it;
				// case C
				if(next(it) == cur_my_tokens.end()){ //the end of the equation
					if(cur.flag == 1 && (*prev(it)).op != "^"){ //if num then must be C except case f(x)=x^2
						c = cur.comp;
						if((*prev(it)).op == "-") c.real *= -1;
					}
					else if(cur.flag == 2){
						if((*prev(it)).op == "-") b.real = -1;
						else if((*prev(it)).op == "+") b.real = 1;
					}
				}
				else if(cur.op == "x"){ // deal with coefficient of x = 1
					if((*(next(next(it)))).flag == 1 && fabs((*(next(next(it)))).comp.real - 2) < eps && (*(next(it))).op == "^"){  //x^2
						if(it == cur_my_tokens.begin()){
							a.real = 1;
						}
						else if((*(prev(it))).flag == 2 && (*(prev(it))).op == "-"){
							a.real = -1;
						}
						else{
							a = (*(prev(it))).comp;
							if(prev(it) != cur_my_tokens.begin() && (*prev(prev(it))).op == "-") a.real *= -1;
						}
					}
					else{
						if(it == cur_my_tokens.begin()){
							b.real = 1;
						}
						else if((*(prev(it))).flag == 2 && (*(prev(it))).op == "-"){
							b.real = -1;
						}
						else if((*(prev(it))).flag == 2 && (*(prev(it))).op == "+"){
							b.real = 1;
						}
						else{
							b = (*(prev(it))).comp;
							if(prev(it) != cur_my_tokens.begin() && (*prev(prev(it))).op == "-") b.real *= -1;
						}
					}
				}
			}
			// print_comp(a);
			// print_comp(b);
			// print_comp(c);
			Complex Constant_4, Constant_2, x_1, x_2;
			Constant_4.real = 4;
			Constant_2.real = 2;
			Complex delta  = sub(mul(b, b), mul(a, mul(c, Constant_4)));
			x_1 = sub(x_1, div(b, mul(Constant_2, a)));
			x_2 = sub(x_2, div(b, mul(Constant_2, a)));
			if(delta.real < 0){
				delta.img = sqrt(-1.0 * delta.real);
				delta.real = 0;
			}
			else{
				delta.real = sqrt(delta.real);
			}
			x_1 = add(x_1, div(delta, mul(Constant_2, a)));
			x_2 = sub(x_2, div(delta, mul(Constant_2, a)));
			cout << "一元二次方程的解为: \n";
			cout << "x_1 = ";
			print_comp(x_1);
			cout << "x_2 = ";
			print_comp(x_2);
			cout << "-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --\n";
			continue;
		}
		flag = 1;
		/* delete the blank */
		ll pos = 0;
		while(pos < s.length()){
			if(s[pos] == ' '){
				if(pos < s.length() - 1 && s[pos + 1] == ' '){
					string tem1 = s.substr(0, pos + 1);
					string tem2 = s.substr(pos + 2, s.length() - pos - 2);
					tem1 += tem2;
					s = tem1;
					continue;
				}
			}
			pos++;
		}
		/* check blank valid */
		ll len = s.length() - 1;
		for(int i = 0; i < len; i++){
			if(s[i] == ' '){
				if(i == 0 || i == len - 1){
					flag = 0;
					tag = 5;
					print_s(cur, i, tag);
					break;
				}
				else{
					if(('0' <= s[i - 1] && s[i - 1] <= '9') && ('0' <= s[i + 1] && s[i + 1] <= '9')){
						flag = 0;
						tag = 5;
						print_s(cur, i, tag);
						break;
					}
				}
			}
		}
		if(!flag) continue;
		pos = 0;
		while(pos < s.length()){
			if(s[pos] == ' '){
				string tem1 = s.substr(0, pos);
				string tem2 = s.substr(pos + 1, s.length() - pos - 1);
				tem1 += tem2;
				s = tem1;
				continue;
			}
			pos++;
		}
		//cout << s << endl;
		check(s, flag, tag);
		if(!flag) continue;
		//calculator part
		cout << "结果为: ";
		print_comp(calculator(s));
		cout << "-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --\n";
	}
	cout << "退出程序.\n";
	return 0;
}
