/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
 * Copyright (C) 2021 Ali Alwan <aalwan99@aalwan99-XPS-15-9570>
 * 
 * steganography is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * steganography is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <string>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"



using namespace std;


void convertDTB(int a,char *output)
{
	int i = 0;
	while(a>1)
	{
		if(a%2 == 1)
		{
			output[i] = '1';
			a = (a-1)/2;
		}
		else
		{
			output[i] = '0';
			a /= 2;
		}
		i++;
	}
	output[i] = '1';
	i++;
	while(i<12)
	{
		output[i] = '0';
		i++;
	}
}

int convertBTD(char x[12])
{
	int toReturn = 0;
	for(int i = 0; i < 12; i++)
	{
		toReturn += (int)(x[i] - '0') * pow(2,i);
	}
	return toReturn;
}

int prime(int pr)

{
    int j = sqrt(pr);
    for (int i = 2; i <= j; i++)
    {
        if (pr % i == 0)
            return 0;
    }
    return 1;
}

int main()
{
	int input;
	cout << "Hello, Welcome to the Steganography Program!\n" << endl;
	cout << "Please Select an Option:" << endl;
	cout << "'1' for Key Generation \n'2' for Encryption \n'3' for Decryption \n'4' to Exit" << endl;
	cin >> input;
	while(input!=4)
	{
		while(input != 1 && input != 2 && input != 3 && input != 4)
		{
			cout << "\nInvalid entry. Please try again." << endl;
			cout << "Please Select an Option:" << endl;
			cout << "'1' for Key Generation \n'2' for Encryption \n'3' for Decryption \n'4' to Exit" << endl;
			cin >> input;
		}
		if(input == 1)
		{
			int p, q;
			cout << "\nRSA Key Generation:\nEnter First Prime Number" << endl;
			cin >> p;

			while(prime(p) == 0)
			{
				cout << "\nInvalid Entry. Try Again." << endl;
				cout << "Enter First Prime Number" << endl;
				cin >> p;
			}
			
			cout << "\nEnter Another Prime Number" << endl;
			cin >> q;

			while(prime(q) == 0 || q == p)
			{
				cout << "\nInvalid Entry. Try Again." << endl;
				cout << "Enter Another Prime Number" << endl;
				cin >> q;
			}


			int n = p*q;
			int phi = (p-1)*(q-1);

			int e,d,flag,k;

			for (int i = 2; i < phi; i++)
			{
				if (phi % i == 0)
				    continue;
				flag = prime(i);
				if (flag == 1 && i != p && i != q)
				{
				    e = i;
					i = phi;
					k = 1;
					while(1)
					{
						k = k + phi;
						if (k % e == 0)
						{
							flag = (k / e);
							break;
						}
					}
				    if (flag > 0)
				        d = flag;
				}
			}

			cout << "\nPublic Key: " << e << endl;
			cout << "Private Key: " << d << endl;
			cout << "Prime Product: " << n << endl;
			cout << "\n" << endl;
		}
		if(input == 2)
		{
			cout << "\nEnter the name of the image you would like to encrypt. (with extension)" << endl;
			char filename[20];
			cin >> filename;
			unsigned char *data;
			int x,y,z;
			data = stbi_load(filename, &x, &y, &z, 0);
			
			if(data == NULL)
			{
				cout << "Error in loading image" << endl;
				goto ERROR;
			}
			cout << "\nPlease enter the secret message to encrypt in '" << filename << "'" << endl;
			string plaintext;
			getline(cin >> ws,plaintext);

// encryption

			int e,n,k;
			cout << "\nRSA Encryption:\nEnter the Public Key" << endl;
			cin >> e;
			cout << "\nEnter the Prime Product" << endl;
			cin >> n;

			unsigned int ciphertext[plaintext.length()];
			int pt;
			for(int i = 0; i < plaintext.length(); i++)
			{
				
				pt = (int)plaintext[i];
				k = 1;
				for(int j = 0; j < e; j++)
				{
					k = k * pt;
					k = k % n;
				}
				ciphertext[i] = k;
			}
			
			
			char bin[plaintext.length()*12+12];

			int len = plaintext.length();
			char len2[12];
			convertDTB(len,len2);
			for(int i = 0; i < 12; i++)
			{					
				bin[i] = len2[i];
			}
			
			for(int i = 0; i < plaintext.length(); i++)
			{
				int a = (int)ciphertext[i];
				char b[12];
				convertDTB(a,b);
				for(int j = 0; j < 12; j++)
				{
					bin[12*(i+1) + j] = b[j];
				}
			}

			for(int i = 0; i < plaintext.length()*12+12; i++)
			{
				if(bin[i] == '0')
				{
					if(data[i]%2 == 1)
					{
						data[i]++;
					}
				}
				else if(bin[i] == '1')
				{
					if(data[i]%2 == 0)
					{
						data[i]++;
					}
				}
			}


			cout << "\nEnter the filename of the encrypted image to save to memory. (with extension)" << endl;
			char encodedFile[20];
			cin >> encodedFile;

			stbi_write_png(encodedFile,x,y,z,data,x*z);

			cout << "\nCongratulations! Your encrypted image has successfully saved to memory.\n\n" << endl;
			
			delete[] data;

		}
		else if(input == 3)
		{
			cout << "\nEnter the name of the image you would like to decrypt. (with extension)" << endl;
			char filename2[20];
			cin >> filename2;
			unsigned char *data2;
			int x,y,z;
			data2 = stbi_load(filename2, &x, &y, &z, 0);
			if(data2 == NULL)
			{
				cout << "Error in loading image" << endl;
				goto ERROR;
			}
			int length;
			char len[12];
			for(int i = 0; i < 12; i++)
			{
				if(static_cast<int>(data2[i])%2 == 1)
					len[i] = '1';
				else
					len[i] = '0';
			}
			length = convertBTD(len);

			int ciphertext[length];

			for(int i = 0; i < length; i++)
			{
				char b[12];
				for(int j = 0; j < 12; j++)
				{
					if(static_cast<int>(data2[12*(i+1) + j])%2 == 1)
						b[j] = '1';
					else
						b[j] = '0';
				}
				int byte = convertBTD(b);
				ciphertext[i] = byte;
			}

// decryption

			int d,n;
			cout << "\nRSA Decryption:\nEnter the Private Key" << endl;
			cin >> d;
			cout << "\nEnter the Prime Product" << endl;
			cin >> n;
			
			char plaintext[length];
			int ct,k;
			for(int i = 0; i < length; i++)
			{
				ct = (int)ciphertext[i];
				k = 1;
				for(int j = 0; j < d; j++)
				{
					k = k * ct;
					k = k % n;
				}
				plaintext[i] = k;
			}
			
			cout << "\nThe encoded message is :" << endl;
			for(int i = 0; i < sizeof(plaintext); i++)
				cout << plaintext[i];
			cout << "\n\n" << endl;
			
			delete[] data2;
		}
		ERROR:;
		cout << "Please Select an Option:" << endl;
		cout << "'1' for Key Generation \n'2' for Encryption \n'3' for Decryption \n'4' to Exit" << endl;
		cin >> input;
	}
	return 0;
}

