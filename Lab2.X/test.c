#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	int i = 0;
	int flag = 0;
	int a = 0;
	float b = 0;
	char str[10]="";
	int length;
	printf("Please enter a string of numbers:\n");
	while(1){
		scanf("%s",str); // 鍏堝瓨鎴愬瓧绗︿覆
		length = strlen(str);
		for(i = 0; i < length; i++){
			if(str[i] == '.'){
				if(flag == 0)
					flag = 1;
				else
					break;
			}
			if(str[i] != '.' && (str[i] < '0' ||  str[i] > '9')){
				break;
			}
		}

		if(i == length){
			if(flag){
				sscanf(str, "%f", &b); // 鍐嶄粠瀛楃涓叉牸寮忓寲鎴愭诞鐐瑰瀷
				printf("You entered a decimal:%f\n", b);
				break;
			}
			else{
				sscanf(str, "%d", &a); // 鍐嶄粠瀛楃涓叉牸寮忓寲鎴愭暣鍨�
				printf("You entered an integer:%d\n", a);
				break;
			}
		}
		else{
			flag = 0;
			printf("What you entered is not a number. Please re-enter it\n");
		}
	}
	getchar();
	getchar();
	return 0;
}
