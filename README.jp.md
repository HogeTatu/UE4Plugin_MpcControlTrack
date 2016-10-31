# UE4Plugin_MpcControlTrack
シーケンサーからマテリアルパラメータコレクションのプロパティを変更できるようにするプラグインです。

![MpcControlTrackDemo_01](https://github.com/HogeTatu/UE4Plugin_MpcControlTrack/blob/master/DocImage/MpcControlTrackDemo_01.png)

## 準備

リポジトリをクローンもしくはZIPをダウンロードした後、MpcControlTrackディレクトリをプロジェクトのプラグインディレクトリに配置します。

```
[プロジェクト名]/Plugins/MpcControlTrack
```

## 使い方

1. 任意のMaterialParameterCollectionアセットを作成します。  
![MpcControlTrackDemo_03](https://github.com/HogeTatu/UE4Plugin_MpcControlTrack/blob/master/DocImage/MpcControlTrackDemo_03.png)

1. MpcOwnerActorを継承したアクターを作成します。  
![MpcControlTrackDemo_02](https://github.com/HogeTatu/UE4Plugin_MpcControlTrack/blob/master/DocImage/MpcControlTrackDemo_02.png)

1. "Class Defaults"を選択し、"Material Parameter Collection"プロパティにアセットを設定します。  
![MpcControlTrackDemo_07](https://github.com/HogeTatu/UE4Plugin_MpcControlTrack/blob/master/DocImage/MpcControlTrackDemo_07.png)

1. MaterialParameterCollectionに追加したプロパティと同名のプロパティを追加し, "Expose to Cinematics"にチェックを入れます。  
![MpcControlTrackDemo_04](https://github.com/HogeTatu/UE4Plugin_MpcControlTrack/blob/master/DocImage/MpcControlTrackDemo_04.png)

1. アクターをシーケンサーエディターにドラッグアンドドロップします。  
![MpcControlTrackDemo_05](https://github.com/HogeTatu/UE4Plugin_MpcControlTrack/blob/master/DocImage/MpcControlTrackDemo_05.png)

1. プロパティトラックを追加します。  
![MpcControlTrackDemo_06](https://github.com/HogeTatu/UE4Plugin_MpcControlTrack/blob/master/DocImage/MpcControlTrackDemo_06.png)

## サンプルプロジェクト

MpcControlTrackDemoがサンプルプロジェクトです。  
MpcControlTrackDemo.uprojectを起動し、動作と実装例を確認してください。  

## ライセンス

[MIT](/LICENSE "LICENSE")

以下、[こちら](http://osdn.jp/projects/opensource/wiki/licenses%2FMIT_license)からの引用です。

>以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェア」）の複製を取得するすべての人に対し、ソフトウェアを無制限に扱うことを無償で許可します。これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および/または販売する権利、およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。
>
>上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。
>
>ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。ここでいう保証とは、商品性、特定の目的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。 作者または著作権者は、契約行為、不法行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請求、損害、その他の義務について何らの責任も負わないものとします。

## 問い合わせ

バグがあった場合は [@HogeTatu](https://twitter.com/HogeTatu) までご連絡頂けると助かります。  
ただ、対応時期に関しては保証できません。  
プルリクエスト大歓迎です。  
