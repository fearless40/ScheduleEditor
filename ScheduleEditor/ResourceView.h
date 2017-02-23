#pragma once
class ResourceView
{
public:
	ResourceView();
	~ResourceView();

	void initalize();
	
	winrt::Windows::UI::Xaml::FrameworkElement xaml_get();

private:
	

private:
	winrt::Windows::UI::Xaml::Controls::StackPanel mBody;
	winrt::Windows::UI::Xaml::Controls::TextBlock mName;
	winrt::Windows::UI::Xaml::Controls::StackPanel mSlotsContainer;
	//std::vector<winrt::Windows::UI::Xaml::Controls::TextBlock> mSlots;
	winrt::Windows::UI::Xaml::Controls::GridView mData;
	
};

