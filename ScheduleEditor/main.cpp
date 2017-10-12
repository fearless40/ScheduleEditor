#include "pch.h"
#include <vector>
#include <memory>

#include "AppUI.h"
#include "ResourceView.h"

using namespace winrt;

using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::UI;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::UI::Xaml::Media;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Graphics::Imaging;
using namespace winrt::Windows::Media::Ocr;
using namespace winrt::Windows::Storage::Pickers;

struct App : ApplicationT<App>
{
	std::unique_ptr<ResourceView> rView{ nullptr };

	void OnLaunched(LaunchActivatedEventArgs const &)
	{
		/*
		TextBlock block;

		block.FontFamily(FontFamily(L"Segoe UI Semibold"));
		block.FontSize(72.0);
		block.Foreground(SolidColorBrush(Colors::Orange()));
		block.VerticalAlignment(VerticalAlignment::Center);
		block.TextAlignment(TextAlignment::Center);
		block.TextWrapping(TextWrapping::Wrap);
		
		Window window = Window::Current();
		window.Content(block);
		window.Activate();
		
		Async(block);
		*/
		Window window = Window::Current();

		AppUI::get().initalize();
		AppUI::get().statusbar_set(L"Yo");

		rView = std::make_unique<ResourceView>();
		rView->initalize();

		AppUI::get().content_set(rView->xaml_get());

		window.Activate();
		
	}

	fire_and_forget Async(TextBlock block)
	{
		FileOpenPicker picker;
		picker.FileTypeFilter().Append(L".png");
		picker.SuggestedStartLocation(PickerLocationId::PicturesLibrary);
		auto file = co_await picker.PickSingleFileAsync();

		if (file == nullptr)
		{
			return;
		}

		thread_context ui_thread;
		co_await resume_background();

		auto stream = co_await file.OpenAsync(FileAccessMode::Read);
		auto decoder = co_await BitmapDecoder::CreateAsync(stream);
		auto bitmap = co_await decoder.GetSoftwareBitmapAsync();
		auto engine = OcrEngine::TryCreateFromUserProfileLanguages();
		auto result = co_await engine.RecognizeAsync(bitmap);

		co_await ui_thread;
		block.Text(result.Text());
	}
};

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
	Application::Start([](auto &&) { make<App>(); });
}