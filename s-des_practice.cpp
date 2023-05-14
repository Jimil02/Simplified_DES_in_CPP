#include <bits/stdc++.h>
using namespace std;

string left_shift_1(string a){
    string shifted="";  
        for(int i = 1; i < a.length(); i++){ 
            shifted += a[i]; 
        } 
        shifted += a[0];   
    return shifted;
}
string left_shift_2(string a){
    a = left_shift_1(a);
    a = left_shift_1(a);
    return a;
}
string convertDecimalToBinary(int decimal)
{
	string binary;
    while(decimal != 0) {
		binary = (decimal % 2 == 0 ? "0" : "1") + binary; 
		decimal = decimal/2;
	}
	while(binary.length() < 4){
		binary = "0" + binary;
	}
    return binary;
}

int convertBinaryToDecimal(string binary)
{
    int decimal = 0;
	int counter = 0;
	int size = binary.length();
	for(int i = size-1; i >= 0; i--)
	{
    	if(binary[i] == '1'){
        	decimal += pow(2, counter);
    	}
    counter++;
	}
	return decimal;
}
string XOR(string a, string b){ 
	string result = ""; 
	int size = b.size();
	for(int i = 0; i < size; i++){ 
		if(a[i] != b[i]){ 
			result += "1"; 
		}
		else{ 
			result += "0"; 
		} 
	} 
	return result; 
}

string sbox(int arr[4][4], string a){
    string r ="";
    string c ="";
    r = a[0];
    r+=a[3];
    c = a[1];
    c+=a[2];
    cout<<"row "<<r<<"\t";
    cout<<"col "<<c<<"\n";
    int row = convertBinaryToDecimal(r);
    int col = convertBinaryToDecimal(c);
    cout<<"DecRow "<<row<<"\t";
    cout<<"DecCol "<<col<<"\n";
    cout<<"SboxResult "<<arr[row][col]<<"\n";
    string result = convertDecimalToBinary(arr[row][col]);
    cout<<"result_Sbox "<<result<<"\n";
    return result;
}

string round(string left, string right, string key){
    int expand[8] = {3,0,1,2,1,2,3,0};
    int p4[4] = {1,3,2,0};
    int s0[4][4] ={{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}};
    int s1[4][4] ={{0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3}};
    string expand_output="";
    for(int i=0;i<8;i++){
        expand_output += right[expand[i]];
    }
    string xor_result = XOR(expand_output,key);
    string left1="";
    string right1="";
    for(int i=0;i<8;i++){
        if(i<4 && i>=0){
            left1 += xor_result[i];
        }
        else{
            right1 += xor_result[i];
        }
    }
    string sbox1 = sbox(s0,left1); 
    string sbox2 = sbox(s1,right1);
    string sbox_result = "";
    sbox_result = sbox1;
    sbox_result += sbox2;
    string p4_output=""; 
    for(int i=0;i<4;i++){
        p4_output += sbox_result[p4[i]];
    }
    string result = XOR(left,p4_output);
    cout<<"round_result "<<result<<"\n";
    return result;
}
void encrypt(string pt, string k1, string k2){
    int IP[8] = {3,5,2,7,4,0,1,6};
    int IP_inverse[8] = {4,1,3,5,7,2,0,6};
    string ip_output="";
    for (int i=0;i<8;i++){
        ip_output += pt[IP[i]];
    }
    string left="";
    string right="";
    for(int i=0; i<8; i++){
        if(i<4 && i>=0){
            left += ip_output[i];
        }
        else{
            right += ip_output[i];
        }
    }
    string round1 = round(left,right,k1);
    left = right;
    right = round1;
    string round2 = round(left,right,k2);
    string before_ct = round2 + right;
    string cipher_text ="";
    for(int i=0;i<8;i++){
        cipher_text += before_ct[IP_inverse[i]];
    }
    cout<<"CipherText is : "<<cipher_text<<"\n";
}
void key_generation(string s, string pt){
    int p10[10] = {3,5,2,7,4,0,1,9,8,6};
    int p8[8] = {5,7,0,9,6,1,4,3};
    string p10_key="";
    string k1="";
    string k2="";
    for(int i=0; i<10; i++){
        p10_key += s[p10[i]];
    }
    string left="";
    string right="";
    for(int i=0; i<10; i++){
        if(i<5 && i>=0){
            left += p10_key[i];
        }
        else{
            right += p10_key[i];
        }
    }
    // cout<<left<<"\n";
    // cout<<right<<"\n";
    left = left_shift_1(left);
    right = left_shift_1(right);
    string p8_input1 = left + right;

    for(int i=0; i<8; i++){
        k1 += p8_input1[p8[i]];
    }
    cout<<"k1="<<k1<<"\n";
    left = left_shift_2(left);
    right = left_shift_2(right);
    string p8_input2 = left + right;

    for(int i=0; i<8; i++){
        k2 += p8_input2[p8[i]];
    }
    cout<<"k2="<<k2<<"\n";

    encrypt(pt,k1,k2);

}

int main(){
    string s = "1001011100";
    string pt = "11110000";
    key_generation(s,pt);
}