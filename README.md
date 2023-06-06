# RSA-Encrypted-Image-Steganography

This project is an Image Stegnaography program written in C++ that also incorporates RSA encryption for added security. There are three key functions to this software program:
1. Key Generation - This phase creates the public and private key that can be used by the sender and receiver to transmit secure, encrypted information. 
2. RSA Encryption and LSB Encoding - A steganographic image is created by encoding the hidden information into a cover image file through LSB encoding. The secret message gets embedded in the image file as ciphertext from RSA encryption using the generated public key.
3. LSB Decoding and RSA Decryption - During the decoding process, the least-significant bits of the steganographic image are read to extract the embedded ciphertext in binary form, which is then converted into decimal form. The ciphertext is decrypted using RSA algorithm if the appropriate private key is entered into the program, allowing the secret message to be displayed to the authorized receiver.

An illustration of the overall process of this software program can be seen with the two images below.

![image](https://github.com/ali-alwan99/RSA-Encrypted-Image-Steganography/assets/128723860/f39e9856-918c-4a58-99fc-9b940ddedf0b)

![image](https://github.com/ali-alwan99/RSA-Encrypted-Image-Steganography/assets/128723860/0cbccf59-55fd-45cd-8906-af4cb6db62d7)
