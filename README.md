# UE4Plugin_MpcControlTrack
It is a plugin to control material parameter collection's properties from sequencer.

[日本語README](/README.jp.md "README.jp.md")

![MpcControlTrackDemo_01](https://github.com/HogeTatu/UE4Plugin_MpcControlTrack/blob/master/DocImage/MpcControlTrackDemo_01.png)

## Getting Started

After clone repository or download ZIP, and Place the MpcControlTrack directory to the plugin directory of the project.

```
[ProjectName]/Plugins/MpcControlTrack
```

## Usage

1. Create and edit the MaterialParameterCollection asset.  
![MpcControlTrackDemo_03](https://github.com/HogeTatu/UE4Plugin_MpcControlTrack/blob/master/DocImage/MpcControlTrackDemo_03.png)

1. Create the actor inherited MpcOwnerActor.  
![MpcControlTrackDemo_02](https://github.com/HogeTatu/UE4Plugin_MpcControlTrack/blob/master/DocImage/MpcControlTrackDemo_02.png)

1. Add a property with the same name as the added properties in the MaterialParameterCollection, check the "Expose to Cinematics".  
![MpcControlTrackDemo_04](https://github.com/HogeTatu/UE4Plugin_MpcControlTrack/blob/master/DocImage/MpcControlTrackDemo_04.png)

1. Drag and drop the actor on the sequencer editor.  
![MpcControlTrackDemo_05](https://github.com/HogeTatu/UE4Plugin_MpcControlTrack/blob/master/DocImage/MpcControlTrackDemo_05.png)

1. Add the property track.  
![MpcControlTrackDemo_06](https://github.com/HogeTatu/UE4Plugin_MpcControlTrack/blob/master/DocImage/MpcControlTrackDemo_06.png)

## Example project

MpcControlTrackDemo is a example project.  
Start MpcControlTrackDemo.uproject, please check the example operations and implementation.  

## License

[MIT](/LICENSE "LICENSE")

## Contact

[@HogeTatu](https://twitter.com/HogeTatu)
