#include "nnetworkinfo.h"

NNetworkInfoForm::NNetworkInfoForm(QWidget *parent)
	:QWidget(parent)
{
	setupUi(this);
}

NNetworkInfoForm::~NNetworkInfoForm()
{

}

void NNetworkInfoForm::updateNetworkInfo(NNetwork *net)
{
	if (!net)
		return;

	QString enc_string;

	network->setText(net->getEssid());
	hidden->setText(net->isHidden() ? tr("yes") : tr("no"));
    signal->setText(QString::number(net->getStrength()) + "%");
    mode->setText((net->getMode() == IW_MODE_INFRA) ? tr("Infrastructure") : tr("Ad-Hoc"));
    freq->setText(QString::number(net->getFrequency() / 1000000000) + tr("GHz"));

	if (net->getCapabilities() & NM_802_11_CAP_PROTO_WEP)
			enc_string.append("WEP");
	if (net->getCapabilities() & NM_802_11_CAP_PROTO_WPA) {
		if (!enc_string.isNull())
			enc_string.append(' ');
		enc_string.append("WPA");
	}
	if (net->getCapabilities() & NM_802_11_CAP_PROTO_WPA2) {
		if (!enc_string.isNull())
			enc_string.append(' ');
		enc_string.append("WPA2");
	}
	if (net->getCapabilities() & NM_802_11_CAP_KEY_MGMT_802_1X) {
		if (!enc_string.isNull())
			enc_string.append(' ');
		enc_string.append("Enterprise");
	}

	if (enc_string.isNull())
		enc_string.append("None");
	encrypt->setText(enc_string);
    rate->setText(QString::number(net->getRate()/1024) + "Mb/s");
}

void NNetworkInfoForm::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Left:
		emit quit(this);
		break;
	default:
		break;
	}

	e->ignore();
}
