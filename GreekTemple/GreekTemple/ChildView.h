/**
 *
 * Greek Temple
 *
 * MIT License
 *
 * Copyright (c) 2023 Retro Technique
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#pragma once

class CChildView : public retro::gl::CRenderWindow
{
#pragma region Constructors

public:

	CChildView();
	virtual ~CChildView();

#pragma endregion
#pragma region Overridables

protected:
	
	BOOL PreCreateWindow(CREATESTRUCT& cs) override;

#pragma endregion
#pragma region Implementations

private:

	HRESULT LoadTextureToGPU(LPCTSTR lpszFileName, UINT uID, INT nLevels);
	HRESULT LoadTextureFromFile(LPCTSTR lpszFileName, IWICBitmap** ppBitmap) const;

#pragma endregion
#pragma region Messages

protected:
	
	DECLARE_MESSAGE_MAP()

protected:

	afx_msg void OnPaint();

public:

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();

#pragma endregion

};

