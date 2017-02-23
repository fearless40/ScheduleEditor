#include "pch.h"
#include <vector>
#include "ResourceView.h"

using namespace winrt::Windows::UI;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::UI::Xaml::Media;


ResourceView::ResourceView()
{
}


ResourceView::~ResourceView()
{
}

void ResourceView::initalize()
{
	mBody.Orientation(Orientation::Horizontal);
	mBody.BorderThickness({ 1,1,1,1 });
	mBody.BorderBrush(SolidColorBrush(Colors::Black()));
	
	mName.Text(L"Spivack");
	mName.VerticalAlignment(VerticalAlignment::Center);
	mName.Padding({ 0,0,4,0 });

	Thickness bThickness{ 0,0,0,1 };

	for (auto i : { L"7-9AM",L"9-2PM",L"2-4pm",L"4-6pm" }) {
		auto slot = TextBlock();
		auto border = Border();
		slot.Text(i);
		border.BorderThickness(bThickness);
		border.BorderBrush(SolidColorBrush(Colors::LightGray()));
		border.Child(slot);
		mSlotsContainer.Children().Append(border);
	}

	mSlotsContainer.Background(SolidColorBrush(Colors::LightYellow()));
	mSlotsContainer.Orientation(Orientation::Vertical);
	mSlotsContainer.VerticalAlignment(VerticalAlignment::Center);
	
	mBody.Children().Append(mName);
	mBody.Children().Append(mSlotsContainer);

	



	//mData.ItemsPanel(ItemWrap.as<ItemsPanelTemplate>());
	
	for (auto i : { L"IVL",L"IVL",L"HC",L"HC",L"IR",L"IR",L"ET",L"ET" })
	{
		auto data = TextBox();
		data.Text(i);
		data.Padding({ 0,0,0,0 });
		data.Margin({ 0,0,0,0 });
		mData.Items().Append(data);
	}

	
	mData.MinHeight = 0;
	mData.MaxHeight = 0;

	mBody.Children().Append(mData);
	
	mData.Loaded([this](winrt::Windows::IInspectable const &, const winrt::Windows::UI::Xaml::RoutedEventArgs &) {
		auto iwp = mData.ItemsPanelRoot().as<ItemsWrapGrid>();
		iwp.MaximumRowsOrColumns(4);
		iwp.Orientation(Orientation::Vertical);
		iwp.Margin({ 0,0,0,0 });
		iwp.GroupPadding({ 0,0,0,0 });
	});

	mData.
}

FrameworkElement ResourceView::xaml_get()
{
	return mBody.as<FrameworkElement>();
}
