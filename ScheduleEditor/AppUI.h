#pragma once

class AppUI
{
public:
	AppUI();
	~AppUI();

	void initalize();
	
	void content_vert();
	void content_horiz();
	void content_clear();
	void content_set(winrt::Windows::UI::Xaml::FrameworkElement & const element);
	void statusbar_set(std::wstring value);
	void statusbar_clear();

	static AppUI & get();

private:
	winrt::Windows::UI::Xaml::Controls::StackPanel mContent{ nullptr };
	winrt::Windows::UI::Xaml::Controls::StackPanel mTop{ nullptr };
	winrt::Windows::UI::Xaml::Controls::StackPanel mMiddle{ nullptr };
	winrt::Windows::UI::Xaml::Controls::StackPanel mBottom{ nullptr };
	winrt::Windows::UI::Xaml::Controls::TextBlock mStatusBar{ nullptr };
};

