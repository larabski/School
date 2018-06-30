<img src="https://i.imgur.com/L0NLajX.png" alt="FCT Logo" align="right" height="50" />

# Multimedia Computing

The goal of this semester-long project was to design and develop a multimedia video player desktop app with built-in timeline generation and metadata-based searching. It was done in groups of two students.

The project uses [openFrameworks](https://github.com/openframeworks/openFrameworks) with some third-party addons (which you can see in the `addons.make` file), [openCV](https://github.com/opencv/opencv) and C++ 11. Besides functionality requirements, we had **total freedom** to design the UI and to architecture the application itself. It was developed in macOS, but can be ported to Windows with the help of the [oF Project Generator](https://github.com/openframeworks/projectGenerator).

On the `other` folder, you can find some extra information:
- The final report presents a state-of-the-art study and insights on the structure of our project and algorithms used.
- A very concise user manual shows how to interact with the app on a basic level.
- The initial UI mocks can also be found there.

## Features

- Import and process videos of different formats.
- Automatically generate a timeline based on similarity for several user-selected parameters.
- Visualize a single video's metadata (luminance, texture characteristics, rythm, ...).
- Play a video's representative frames on mouse hover (based on scene-cut detection).
- Remove videos from the timeline or re-organize it.
- Apply transition effects to the timeline.
