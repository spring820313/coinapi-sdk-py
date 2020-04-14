import sys
sys.path.append("./build/Release")

import coinapisdk

b = coinapisdk.CoinApi.createAllCoinMnemonicCode()
print b

kp = coinapisdk.KeyPath()
kp.path1 = 44
kp.path2 = 60
kp.path3 = 0
kp.path4 = 0
kp.path5 = 0
kp.hd1 = True
kp.hd2 = True
kp.hd3 = False
kp.hd4 = False
kp.hd5 = False
kp.symbol = 'BTC'

np = coinapisdk.NetParams()
np.symbol = 'BTC'
np.coinType = coinapisdk.CoinType.BTC
np.nettype = coinapisdk.NetworkType.TEST
np.keyPath = kp
np.version = 2
np.HDprivate = 0x04358394
np.HDpublic = 0x043587CF
np.P2KH = 0x6f
np.P2SH = 0xC4
np.keyprefixes = 239
np.ApiVersion = 2
np.N = 32768
np.R = 8
np.P = 1

words = ' '.join(b)
print words
bw = coinapisdk.CoinApi.createWallet(words, '12345', np)
print bw.pubkey
print bw.address
print bw.btSeed.pwdhash
print bw.btSeed.encryptedSeed.initialisationVector
print bw.btSeed.encryptedSeed.encryptedBytes

key = coinapisdk.CoinApi.getPriKeyFromBtSeed(bw.btSeed, '12345', np)
print key

params = coinapisdk.BtcCreateSignTransactionParams()
params.fromAddress = 'mvn82Jz4SyTtowEyviiL3cMc5rujRd81os'
params.priKey = 'cPMpp4dVWME5jFMZEoj2FeWVkVRhnyRNwFprY4jkWQVJtjVBTWyM'
params.feePerKb = 10000
params.sendAddress = 'mjRdBFR1cA6rLUz7nZGrG6hLEWiDgGn8r7'
params.sendValue = 100000000

voutList = []

vout1 = coinapisdk.BtcvoutForm()
vout1.hash = 'c4d54e09c1df71b2f090fcffcbc2901418154ff7795f6da327f549f02b84a3a9'
vout1.value = 1000000000
vout1.n = 1
vout1.coinBase = False
voutList.append(vout1)

vout2 = coinapisdk.BtcvoutForm()
vout2.hash = '215e8f72f39fad874cfab0deed11a80f24f967a84079fb56ddf53ea02e308986'
vout2.value = 1000000000
vout2.n = 0
vout2.coinBase = False
voutList.append(vout2)

params.btcvoutFormList = voutList

resultMap = coinapisdk.CoinApi.createSignTransaction(params, np)
for k in resultMap.keys():
	print(k+':' + resultMap[k])