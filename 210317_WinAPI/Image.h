#pragma once
#include "config.h"

class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,		// ������Ʈ ��ü�� ���� ��ų �̹���
		FILE,			// �ܺο��� �ε��� �̹���
		EMPTY,			// ��ü ���� �̹���
		END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;		// ���ҽ��� ������ ID
		HDC hMemDC;			// �׸��⸦ �ְ��ϴ� �ڵ�
		HBITMAP hBitmap;	// �̹��� ����
		HBITMAP hOldBit;	// ���� �̹��� ����
		float width;			// �̹��� ���� ũ��
		float height;			// �̹��� ���� ũ��
		BYTE loadType;		// �ε� Ÿ��

		// ���ĺ���
		HDC hBlendDC;
		HBITMAP hBlendBit;
		HBITMAP hOldBlendBit;

		// �ִϸ��̼� ���� (�����ӵ�����)
		float maxFrameX;
		float maxFrameY;
		float frameWidth;
		float frameHeight;
		float currFrameX;
		float currFrameY;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_KIND::EMPTY;

			hBlendDC = NULL;
			hBlendBit = NULL;
			hOldBlendBit = NULL;

			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			currFrameX = 0;
			currFrameY = 0;
		};
	} IMAGE_INFO, * LPIMAGE_INFO;

private:
	IMAGE_INFO* imageInfo;		// �̹��� ���� ����ü ������
	//LPIMAGE_INFO imageInfo;
	bool isTransparent;
	COLORREF transColor;

	BLENDFUNCTION blendFunc;

public:
	// �� ��Ʈ�� �̹����� ����� �Լ�
	HRESULT Init(int width, int height);

	// ���Ϸκ��� �̹����� �ε��ϴ� �Լ�
	HRESULT Init(const char* fileName, int width, int height, bool isTransparent = FALSE, COLORREF transColor = FALSE);

	// ���Ϸκ��� �̹����� �ε��ϴ� �Լ�
	HRESULT Init(const char* fileName, int width, int height, 
		int maxFrameX, int maxFrameY,
		bool isTransparent = FALSE, COLORREF transColor = FALSE);

	// ȭ�鿡 ���
	void Render(HDC hdc, int destX = 0, int destY = 0,
		bool isCenterRenderring = false, FPOINT size = { 1,1 });
	void FrameRender(HDC hdc, int destX, int destY,
		float currFrameX, float currFrameY, bool isCenterRenderring = false, float size = 1);
	void AlphaRender(HDC hdc, int destX, int destY,
		bool isCenterRenderring = false);
	void UiBarRender(HDC hdc, int destX, int destY, bool isCenterRenderring, float maxPer, float nowPer);



	void Release();

	// get, set
	HDC GetMemDC()
	{
		if (this->imageInfo)
			return this->imageInfo->hMemDC;
		return NULL;
	}

	void SetMemDC(HDC hdc) 
	{
		if (this->imageInfo)
			this->imageInfo->hMemDC = hdc;
	}

	BLENDFUNCTION* GetBlendFunc() { return &(this->blendFunc); }

	int GetWidth() { return this->imageInfo->width; }
	int GetHeight() { return this->imageInfo->height; }
	float GetFrameWidth() { return this->imageInfo->frameWidth; }
	float GetFrameHeight() { return this->imageInfo->frameHeight; }

	IMAGE_INFO* const  GetImageInfo() { return this->imageInfo; }
};

