#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#undef HAVE_LONG_LONG

#include <iostream>
#include <string>
#include <vector>
#include "coinapi/common/coin_code.hpp"
#include "coinapi/common/CommonCoinApi.hpp"


namespace py = pybind11;
using namespace std;

class CoinApi
{
public:
	static std::vector<std::string> createAllCoinMnemonicCode()
	{
		return CommonCoinApi().createAllCoinMnemonicCode();
	}

	static  bool checkMnemonicCode(std::vector<std::string> words)
	{
		return CommonCoinApi().checkMnemonicCode(words);
	}

	static  BtWallet createWallet(string words, string password, NetParams netParams)
	{
		BtWallet bw;
		CommonCoinApi().createWallet(words, password, netParams, bw);
		return bw;
	}

	static string getPriKeyFromBtSeed(BtSeed btSeed, string password, NetParams netParams)
	{
		return CommonCoinApi().getPriKeyFromBtSeed(btSeed, password, netParams);
	}

	static map<string, string> createSignTransaction(CreateSignTransactionParams* createSignTransactionParams, NetParams netParams)
	{
		map<string, string> result;
		CommonCoinApi().createSignTransaction(createSignTransactionParams, netParams, result);
		return result;
	}
};

void init_coinapi(py::module m)
{
	py::class_<KeyPath> keypath_class(m, "KeyPath");
	keypath_class.def(py::init())
		.def_property("path1", &KeyPath::getPath1, &KeyPath::setPath1)
		.def_property("path2", &KeyPath::getPath2, &KeyPath::setPath2)
		.def_property("path3", &KeyPath::getPath3, &KeyPath::setPath3)
		.def_property("path4", &KeyPath::getPath4, &KeyPath::setPath4)
		.def_property("path5", &KeyPath::getPath5, &KeyPath::setPath5)
		.def_property("hd1", &KeyPath::getHd1, &KeyPath::setHd1)
		.def_property("hd2", &KeyPath::getHd2, &KeyPath::setHd2)
		.def_property("hd3", &KeyPath::getHd3, &KeyPath::setHd3)
		.def_property("hd4", &KeyPath::getHd4, &KeyPath::setHd4)
		.def_property("hd5", &KeyPath::getHd5, &KeyPath::setHd5)
		.def_property("symbol", &KeyPath::getSymbol, &KeyPath::setSymbol);

	py::enum_<CoinType>(m, "CoinType")
		.value("BTC", CoinType::BTC)
		.value("ETH", CoinType::ETH)
		.value("WICC", CoinType::WICC)
		.value("BTS", CoinType::BTS)
		.value("AFT", CoinType::AFT)
		.value("LTC", CoinType::LTC)
		.value("SBTC", CoinType::SBTC)
		.value("DOGE", CoinType::DOGE)
		.value("ETC", CoinType::ETC)
		.value("WBTC", CoinType::WBTC)
		.value("ZEC", CoinType::ZEC)
		.value("DSH", CoinType::DSH)
		.value("BCH", CoinType::BCH)
		.value("QTUM", CoinType::QTUM)
		.value("LBTC", CoinType::LBTC)
		.value("NEO", CoinType::NEO)
		.value("GAS", CoinType::GAS)
		.value("XZC", CoinType::XZC)
		.value("USDT", CoinType::USDT)
		.value("BCO", CoinType::BCO)
		.value("BHD", CoinType::BHD)
		.value("EOS", CoinType::EOS)
		.value("MC", CoinType::MC)
		.value("CHAINX", CoinType::CHAINX)
		.value("COSMOS", CoinType::COSMOS)
		.value("NULS", CoinType::NULS)
		.value("COINEX", CoinType::COINEX)
		.value("FIL", CoinType::FIL)
		.export_values();

	py::enum_<NetworkType>(m, "NetworkType")
		.value("MAIN", NetworkType::MAIN)
		.value("TEST", NetworkType::TEST)
		.value("REGTEST", NetworkType::REGTEST)
		.export_values();

	py::class_<NetParams> netparams_class(m, "NetParams");
	netparams_class.def(py::init())
		.def_property("symbol", &NetParams::getSymbol, &NetParams::setSymbol)
		.def_property("coinType", &NetParams::getCoinType, &NetParams::setCoinType)
		.def_property("nettype", &NetParams::getNetType, &NetParams::setNetType)
		.def_property("keyPath", &NetParams::getKeyPath, &NetParams::setKeyPath)
		.def_property("version", &NetParams::getVersion, &NetParams::setVersion)
		.def_property("HDprivate", &NetParams::getHDprivate, &NetParams::setHDprivate)
		.def_property("HDpublic", &NetParams::getHDpublic, &NetParams::setHDpublic)
		.def_property("P2KH", &NetParams::getP2KH, &NetParams::setP2KH)
		.def_property("P2SH", &NetParams::getP2SH, &NetParams::setP2SH)
		.def_property("keyprefixes", &NetParams::getKeyprefixes, &NetParams::setKeyprefixes)
		.def_property("ApiVersion", &NetParams::getApiVersion, &NetParams::setApiVersion)
		.def_property("N", &NetParams::getN, &NetParams::setN)
		.def_property("R", &NetParams::getR, &NetParams::setR)
		.def_property("P", &NetParams::getP, &NetParams::setP);

	py::class_<EncryptedData> encrypteddata_class(m, "EncryptedData");
	encrypteddata_class.def(py::init())
		.def_property("initialisationVector", &EncryptedData::getIV, &EncryptedData::setIV)
		.def_property("encryptedBytes", &EncryptedData::getEncryptedBytes, &EncryptedData::setEncryptedBytes);

	py::class_<BtSeed> btseed_class(m, "BtSeed");
	btseed_class.def(py::init())
		.def_property("seed", &BtSeed::getSeed, &BtSeed::setSeed)
		.def_property("mnemonicCode", &BtSeed::getMnemonicCode, &BtSeed::setMnemonicCode)
		.def_property("encryptedMnemonicCode", &BtSeed::getEncryptedMnemonicCode, &BtSeed::setEncryptedMnemonicCode)
		.def_property("encryptedSeed", &BtSeed::getEncryptedSeed, &BtSeed::setEncryptedSeed)
		.def_property("creationTimeSeconds", &BtSeed::getCreationTimeSeconds, &BtSeed::setCreationTimeSeconds)
		.def_property("pwdhash", &BtSeed::getPwdhash, &BtSeed::setPwdhash)
		.def_property("randomSalt", &BtSeed::getRandomSalt, &BtSeed::setRandomSalt);

	py::class_<BtWallet> btwallet_class(m, "BtWallet");
	btwallet_class.def(py::init())
		.def_property("btSeed", &BtWallet::getBtSeed, &BtWallet::setBtSeed)
		.def_property("pubkey", &BtWallet::getPubkey, &BtWallet::setPubkey)
		.def_property("address", &BtWallet::getAddress, &BtWallet::setAddress)
		.def_property("symbol", &BtWallet::getSymbol, &BtWallet::setSymbol);

	py::enum_<TxType>(m, "TxType")
		.value("TX_NONE", TxType::TX_NONE)
		.value("TX_LBTC_REGISTER", TxType::TX_LBTC_REGISTER)
		.value("TX_LBTC_VOTE", TxType::TX_LBTC_VOTE)
		.value("TX_LBTC_CANCELVOTE", TxType::TX_LBTC_CANCELVOTE)
		.value("TX_QTUM_TOKEN_TRANSFER", TxType::TX_QTUM_TOKEN_TRANSFER)
		.value("TX_WICC_REGISTERACCOUNT", TxType::TX_WICC_REGISTERACCOUNT)
		.value("TX_WICC_COMMON", TxType::TX_WICC_COMMON)
		.value("TX_WICC_TRANSFER_SPC", TxType::TX_WICC_TRANSFER_SPC)
		.value("TX_WICC_BET", TxType::TX_WICC_BET)
		.value("TX_WICC_DELEGATE", TxType::TX_WICC_DELEGATE)
		.value("TX_WICC_TRANSFER_COINS", TxType::TX_WICC_TRANSFER_COINS)
		.export_values();

	py::class_<BtcvoutForm> btcvoutform_class(m, "BtcvoutForm");
	btcvoutform_class.def(py::init())
		.def_property("hash", &BtcvoutForm::getHash, &BtcvoutForm::setHash)
		.def_property("value", &BtcvoutForm::getValue, &BtcvoutForm::setValue)
		.def_property("n", &BtcvoutForm::getN, &BtcvoutForm::setN)
		.def_property("coinBase", &BtcvoutForm::getCoinBase, &BtcvoutForm::setCoinBase);

	py::class_<CreateSignTransactionParams> createsigntransactionparams_class(m, "CreateSignTransactionParams");

	py::class_<BtcCreateSignTransactionParams, CreateSignTransactionParams> btccreatesigntransactionparams_class(m, "BtcCreateSignTransactionParams");
	btccreatesigntransactionparams_class.def(py::init())
		.def_property("btSeed", &BtcCreateSignTransactionParams::getBtSeed, &BtcCreateSignTransactionParams::setBtSeed)
		.def_property("fromAddress", &BtcCreateSignTransactionParams::getFromAddress, &BtcCreateSignTransactionParams::setFromAddress)
		.def_property("sendAddress", &BtcCreateSignTransactionParams::getSendAddress, &BtcCreateSignTransactionParams::setSendAddress)
		.def_property("sendValue", &BtcCreateSignTransactionParams::getSendValue, &BtcCreateSignTransactionParams::setSendValue)
		.def_property("feePerKb", &BtcCreateSignTransactionParams::getFeePerKb, &BtcCreateSignTransactionParams::setFeePerKb)
		.def_property("password", &BtcCreateSignTransactionParams::getPassword, &BtcCreateSignTransactionParams::setPassword)
		.def_property("priKey", &BtcCreateSignTransactionParams::getPriKey, &BtcCreateSignTransactionParams::setPriKey)
		.def_property("btcvoutFormList", &BtcCreateSignTransactionParams::getBtcvoutFormList, &BtcCreateSignTransactionParams::setBtcvoutFormList)
		.def_property("recipientsPayFees", &BtcCreateSignTransactionParams::getRecipientsPayFees, &BtcCreateSignTransactionParams::setRecipientsPayFees)
		.def_property("data", &BtcCreateSignTransactionParams::getData, &BtcCreateSignTransactionParams::setData)
		.def_property("txType", &BtcCreateSignTransactionParams::getTxType, &BtcCreateSignTransactionParams::setTxType);

	py::class_<CoinApi> coinapi_class(m, "CoinApi");
	coinapi_class
		.def_static("createAllCoinMnemonicCode", &CoinApi::createAllCoinMnemonicCode)
		.def_static("checkMnemonicCode", &CoinApi::checkMnemonicCode)
		.def_static("createWallet", &CoinApi::createWallet)
		.def_static("getPriKeyFromBtSeed", &CoinApi::getPriKeyFromBtSeed)
		.def_static("createSignTransaction", &CoinApi::createSignTransaction);
}

//////////////////////



PYBIND11_MODULE(coinapisdk, m)
{
    m.doc() = "coinapi sdk plugin"; // optional module docstring
    
	init_coinapi(m);
}