#pragma once

class SkinnyBox
{

public:

	SkinnyBox();
	~SkinnyBox();

	SkinnyBox(const SkinnyBox& _Other) = delete;
	SkinnyBox(SkinnyBox&& _Other) noexcept = delete;
	SkinnyBox& operator=(const SkinnyBox& _Other) = delete;
	SkinnyBox& operator=(SkinnyBox&& _Other) noexcept = delete;

protected:

private:

};

