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
		/*auto border = Border();

		border.BorderBrush(SolidColorBrush(Colors::Silver()));
		border.Padding({ 0,0,0,0 });
		border.Margin({ 0,0,0,0 });
		border.BorderThickness({ 0.5,0.5,0.5,0.5 });
		border.Child(data);*/
		/*data.Text(i);
		data.Padding({ 0,0,0,0 });
		data.Margin({ 0,0,0,0 });
		data.MaxHeight( 20 );
		data.MaxWidth(100);*/

		auto stringValue = winrt::Windows::Foundation::PropertyValue::CreateString(i);
		

		mData.Items().Append(stringValue);
	}

	
	//mData.MinHeight = 0;
	//mData.MaxHeight = 0;

	mBody.Children().Append(mData);
	
	

	mData.Loaded([this](winrt::Windows::Foundation::IInspectable const &, const winrt::Windows::UI::Xaml::RoutedEventArgs &) {
		auto iwp = mData.ItemsPanelRoot().as<ItemsWrapGrid>();
		iwp.MaximumRowsOrColumns(4);
		iwp.Orientation(Orientation::Vertical);
		iwp.Margin({ 0,0,0,0 });
		iwp.GroupPadding({ 0,0,0,0 });
		//iwp.ItemHeight(20);
		//iwp.ItemWidth(100);

		//DataTemplate dt;
		///winrt::Windows::Foundation::IReference<double> pv;
		//winrt::Windows::Foundation::IReference<double> pw;
		//auto pw = winrt::Windows::Foundation::PropertyValue::CreateDouble(5.0);


		//dt.SetValue(FrameworkElement::MaxWidthProperty(), pw);
		//dt.SetValue(FrameworkElement::MaxHeightProperty(), pw);

		//mData.ItemTemplate(dt);
		//auto marg = style.GetValue(FrameworkElement::MarginProperty());
		//auto border = marg.as<Thickness>();
		//border->Top //= 0;
		//border->Bottom = 0;
		//border->Left = 0;
		//border->Right = 0;
		//style.SetValue(FrameworkElement::MarginProperty(), marg );
		
		//winrt::Windows::UI::Xaml::Media::VisualTreeHelper::GetChild()
		//dt = mData.ItemTemplate();
		
		//dt.SetValue(FrameworkElement::MaxWidthProperty(), pw);
		//dt.SetValue(FrameworkElement::MaxHeightProperty(), pw);

		//mData.ItemTemplate(dt);

	});

	

	

	
}

FrameworkElement ResourceView::xaml_get()
{
	return mBody.as<FrameworkElement>();
}
