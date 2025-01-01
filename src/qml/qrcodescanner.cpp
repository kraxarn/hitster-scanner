#include "qml/qrcodescanner.hpp"

#include "ReadBarcode.h"

#include <QVideoFrame>

QrCodeScanner::QrCodeScanner(QObject *parent)
	: QObject(parent),
	urlResolver(new UrlResolver(this))
{
	connect(urlResolver, &UrlResolver::resolved,
		this, &QrCodeScanner::onUrlResolved);
}

auto QrCodeScanner::getSink() const -> QVideoSink *
{
	return sink;
}

void QrCodeScanner::setSink(QVideoSink *sink)
{
	this->sink = sink;
	emit sinkChanged();
}

void QrCodeScanner::scan() const
{
	if (sink == nullptr)
	{
		qWarning() << "Scan failed: no sink";
		return;
	}

	const auto &frame = sink->videoFrame();
	auto image = frame.toImage();

	// Based on:
	// https://invent.kde.org/frameworks/prison/-/blob/master/src/scanner/imagescanner.cpp

	ZXing::ImageFormat imageFormat;

	switch (image.format())
	{
		case QImage::Format_Invalid:
		case QImage::Format_Alpha8:
		case QImage::NImageFormats:
		default:
			qWarning() << "Invalid format:" << image.format();
			return;

		case QImage::Format_Mono:
		case QImage::Format_MonoLSB:
		case QImage::Format_Indexed8:
		case QImage::Format_RGB16:
		case QImage::Format_ARGB8565_Premultiplied:
		case QImage::Format_RGB666:
		case QImage::Format_ARGB6666_Premultiplied:
		case QImage::Format_ARGB8555_Premultiplied:
		case QImage::Format_RGB444:
		case QImage::Format_ARGB4444_Premultiplied:
		case QImage::Format_BGR30:
		case QImage::Format_A2BGR30_Premultiplied:
		case QImage::Format_RGB30:
		case QImage::Format_A2RGB30_Premultiplied:
		case QImage::Format_RGBX64:
		case QImage::Format_RGBA64:
		case QImage::Format_RGBA64_Premultiplied:
		case QImage::Format_RGBX16FPx4:
		case QImage::Format_RGBA16FPx4:
		case QImage::Format_RGBA16FPx4_Premultiplied:
		case QImage::Format_RGBX32FPx4:
		case QImage::Format_RGBA32FPx4:
		case QImage::Format_RGBA32FPx4_Premultiplied:
			image = image.convertedTo(QImage::Format_Grayscale8);
			imageFormat = ZXing::ImageFormat::Lum;
			break;

		case QImage::Format_RGB32:
		case QImage::Format_ARGB32:
		case QImage::Format_ARGB32_Premultiplied:
			imageFormat = ZXing::ImageFormat::XRGB;
			break;

		case QImage::Format_RGB888:
			imageFormat = ZXing::ImageFormat::RGB;
			break;

		case QImage::Format_RGBX8888:
		case QImage::Format_RGBA8888:
		case QImage::Format_RGBA8888_Premultiplied:
			imageFormat = ZXing::ImageFormat::RGBX;
			break;

		case QImage::Format_Grayscale8:
		case QImage::Format_Grayscale16: // TODO
			imageFormat = ZXing::ImageFormat::Lum;
			break;

		case QImage::Format_BGR888:
			imageFormat = ZXing::ImageFormat::BGR;
			break;
	}

	const ZXing::ImageView imageView(image.bits(), image.width(), image.height(),
		imageFormat, static_cast<int>(image.bytesPerLine()));

	ZXing::ReaderOptions options;
	options.setFormats(ZXing::BarcodeFormat::QRCode);

	const auto result = ReadBarcode(imageView, options);
	if (result.format() != ZXing::BarcodeFormat::QRCode)
	{
		return;
	}

	const auto text = result.text(ZXing::TextMode::Plain);
	const QUrl url(QString::fromStdString(text), QUrl::StrictMode);

	if (!url.isValid())
	{
		qWarning() << url.errorString();
		return;
	}

	urlResolver->resolve(url);
}

void QrCodeScanner::onUrlResolved(const QUrl &url)
{
	qInfo() << "Found track ID:" << url.fileName();
}
