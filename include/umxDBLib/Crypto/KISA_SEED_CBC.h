/**
@file KISA_SEED_CBC.h
@brief SEED CBC ��ȣ �˰���
@author Copyright (c) 2013 by KISA
@remarks http://seed.kisa.or.kr/
*/
#pragma once
#pragma warning(disable:4996)	// warning C4996: '_vsnprintf': This function or variable may be unsafe. Consider using _vsnprintf_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
								// warning C4996: 'fopen': This function or variable may be unsafe. Consider using fopen_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.

#ifndef SEED_CBC_H
#define SEED_CBC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef OUT
#define OUT
#endif

#ifndef IN
#define IN
#endif

#ifndef INOUT
#define INOUT
#endif

//typedef unsigned int        DWORD;
//typedef unsigned short      WORD;
//typedef unsigned char       BYTE;

#define BLOCK_SIZE_SEED			16
#define BLOCK_SIZE_SEED_INT		4

#ifndef _KISA_ENC_DEC_
#define _KISA_ENC_DEC_
typedef enum _SEED_ENC_DEC
{
	KISA_DECRYPT,
	KISA_ENCRYPT,
}KISA_ENC_DEC;
#endif

#ifndef _KISA_SEED_KEY_
#define _KISA_SEED_KEY_
typedef struct kisa_seed_key_st 
{
	unsigned int key_data[32];
} KISA_SEED_KEY;
#endif

#ifndef _KISA_SEED_INFO_
#define _KISA_SEED_INFO_
typedef struct kisa_seed_info_st 
{	
	KISA_ENC_DEC	encrypt;				
	unsigned int			ivec[4];				
	KISA_SEED_KEY	seed_key;				
	unsigned int			cbc_buffer[4];			
	int				buffer_length;			
	unsigned int			cbc_last_block[4];		
	int				last_block_flag;		
} KISA_SEED_INFO;
#endif

void SEED_SetKey(IN unsigned char* key);
int SEED_Encrypt(IN unsigned char* plainText, OUT unsigned char* cipherText);
int SEED_Decrypt(IN unsigned char* cipherText, OUT unsigned char* plainText, int cipherlength);
int SEED_Encrypt4(IN unsigned char* plainText, int plainSize, OUT unsigned char* cipherText);

/**
@brief unsigned char �迭�� int �迭�� ��ȯ�Ѵ�.
@param in :��ȯ�� unsigned char ������
@param nLen : ��ȯ�� unsigned char �迭 ����
@return ���ڷ� ���� unsigned char �迭�� int�� ��ȯ�� �����͸� ��ȯ�Ѵ�. (���������� malloc������ free�� �� ����� �Ѵ�)
@remarks ���������� ������ ����� �Լ��� SEED CTR, CBC, HIGHT CTR, CBC�� ������ include �� 
���� �Լ��� ��� �浹 ������ �ڿ� ������ �� �ֵ��� ���带 ���δ�.
*/
unsigned int* chartoint32_for_SEED_CBC( IN unsigned char *in, IN int nLen );

/**
@brief int �迭�� unsigned char �迭�� ��ȯ�Ѵ�.
@param in :��ȯ�� int ������
@param nLen : ��ȯ�� int �迭 ����
@return ���ڷ� ���� int �迭�� char�� ��ȯ�� �����͸� ��ȯ�Ѵ�. (���������� malloc������ free�� �� ����� �Ѵ�)
@remarks ���������� ������ ����� �Լ��� SEED CTR, CBC, HIGHT CTR, CBC�� ������ include �� 
���� �Լ��� ��� �浹 ������ �ڿ� ������ �� �ֵ��� ���带 ���δ�.
*/
unsigned char* int32tochar_for_SEED_CBC( IN unsigned int *in, IN int nLen );

/**
@brief SEED CBC �˰��� �ʱ�ȭ �Լ�
@param pInfo : CBC ���ο��� ���Ǵ� ����ü�ν� ������ �����ϸ� �ȵȴ�.(�޸� �Ҵ�Ǿ� �־�� �Ѵ�.)
@param enc : ��ȣȭ �� ��ȣȭ ��� ����
@param pbszUserKey : ����ڰ� �����ϴ� �Է� Ű(16 unsigned char)
@param pbszIV : ����ڰ� �����ϴ� �ʱ�ȭ ����(16 unsigned char)
@return 0: pInfo �Ǵ� pbszUserKey �Ǵ� pbszIV �����Ͱ� NULL�� ���, 
        1: ����
*/
int SEED_CBC_init( OUT KISA_SEED_INFO *pInfo, IN KISA_ENC_DEC enc, IN unsigned char *pbszUserKey, IN unsigned char *pbszIV );

/**
@brief SEED CBC ���� �� ��ȣȭ/��ȣȭ �Լ�
@param pInfo : SEED_CBC_init ���� ������ KISA_HIGHT_INFO ����ü
@param in : ��/��ȣ�� ( ���� chartoint32_for_SEED_CBC�� ����Ͽ� int�� ��ȯ�� ������)
@param inLen : ��/��ȣ�� ����(unsigned char ����)
@param out : ��/��ȣ�� ����
@param outLen : ����� ��/��ȣ���� ����(unsigned char ������ �Ѱ��ش�)
@return 0: inLen�� ���� 0���� ���� ���, KISA_SEED_INFO ����ü�� in, out�� �� �����Ͱ� �Ҵ�Ǿ��� ���
        1: ����
*/
int SEED_CBC_Process( OUT KISA_SEED_INFO *pInfo, IN unsigned int *in, IN int inLen, OUT unsigned int *out, OUT int *outLen );

/**
@brief SEED CBC ���� ���� �� �е� ó��(PKCS7)
@param pInfo : SEED_CBC_Process �� ��ģ KISA_HIGHT_INFO ����ü
@param out : ��/��ȣ�� ��� ����
@param outLen : ��� ���ۿ� ����� ������ ����(unsigned char ������ �򹮱���)
@return 
- 0 :  inLen�� ���� 0���� ���� ���,
       KISA_SEED_INFO ����ü�� out�� �� �����Ͱ� �Ҵ�Ǿ��� ���
- 1 :  ����
@remarks �е� ���������� 16����Ʈ ������ ó�������� ��ȣȭ �� ��� ���۴� 
�򹮺��� 16����Ʈ Ŀ�� �Ѵ�.(���� 16����Ʈ �� �� �е� ����Ÿ�� 16����Ʈ�� ����.)
*/
int SEED_CBC_Close( OUT KISA_SEED_INFO *pInfo, IN unsigned int *out, IN int *outLen );

/**
@brief ó���ϰ��� �ϴ� �����Ͱ� ���� ��쿡 ���
@param pbszUserKey : ����ڰ� �����ϴ� �Է� Ű(16 unsigned char)
@param pszbIV : ����ڰ� �����ϴ� �ʱ�ȭ ����(16 unsigned char)
@param pbszPlainText : ����� �Է� ��
@param nPlainTextLen : �� ����(unsigned char ������ �򹮱���)
@param pbszCipherText : ��ȣ�� ��� ����
@return ��ȣȭ�� ����� ����(char ����)
@remarks �е� ���������� 16����Ʈ ������ ó�������� pbszCipherText�� �򹮺��� 16����Ʈ Ŀ�� �Ѵ�.
(���� 16����Ʈ �� �� �е� ����Ÿ�� 16����Ʈ�� ����.)
*/
int SEED_CBC_Encrypt( IN unsigned char *pbszUserKey, IN unsigned char *pbszIV, IN unsigned char *pbszPlainText, IN int nPlainTextLen, OUT unsigned char *pbszCipherText );

/**
@brief ó���ϰ��� �ϴ� �����Ͱ� ���� ��쿡 ���
@param pbszUserKey : ����ڰ� �����ϴ� �Է� Ű(16 unsigned char)
@param pszbIV : ����ڰ� �����ϴ� �ʱ�ȭ ����(16 unsigned char)
@param pbszCipherText : ��ȣ��
@param nCipherTextLen : ��ȣ�� ����(unsigned char ������ �򹮱���)
@return ��ȣȭ�� ����� ����(char ����)
@param pbszPlainText : �� ��� ����
*/
int SEED_CBC_Decrypt( IN unsigned char *pbszUserKey, IN unsigned char *pbszIV, IN unsigned char *pbszCipherText, IN int nCipherTextLen, OUT unsigned char *pbszPlainText );

#ifdef  __cplusplus
}
#endif

#endif
