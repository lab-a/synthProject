# SynthMultimedia

Plugin sintetizador desarrollado en **C++** utilizando el framework **JUCE** como proyecto de aprendizaje de síntesis de sonido y desarrollo de aplicaciones de audio. El objetivo del proyecto ha sido implementar desde cero los principales bloques que componen un sintetizador.

## Características

* Oscilador con selección de diferentes formas de onda.
* Envolvente ADSR para controlar la amplitud.
* Filtro con parámetros ajustables.
* Reverb integrada.
* Controles de volumen y panoramización.
* Visualizador de la forma de onda en tiempo real.
* Gestión de parámetros mediante `AudioProcessorValueTreeState`.

## Arquitectura

El proyecto está dividido en varios módulos independientes:

* **DSP**: implementación del oscilador, ADSR, filtro, reverb y controles de volumen/pan.
* **UI**: componentes gráficos de cada módulo y visualizador de la señal.
* **PluginProcessor**: procesamiento de audio y gestión de parámetros.
* **PluginEditor**: construcción de la interfaz gráfica.

Esta separación permite mantener desacoplada la lógica de procesamiento de audio de la interfaz de usuario.

## Capturas

> **Interfaz principal**

**![Imagen de la interfaz](/synthUI.jpg)**

> **Funcionamiento del sintetizador**

**![GIF modificando parámetros y mostrando el visualizador](/sampleSynth.mp4)**

## Tecnologías utilizadas

* C++
* JUCE Framework
* AudioProcessorValueTreeState (APVTS)

## Posibles mejoras

Algunas funcionalidades que podrían incorporarse en futuras versiones:

* Más formas de onda.
* LFO para modulación.
* Más tipos de filtro.
* Presets de usuario.
* Polifonía configurable.
* Efectos adicionales (delay, chorus, etc.).

## Compilación

El proyecto ha sido desarrollado con JUCE y puede abrirse desde el proyecto generado por Projucer (o mediante CMake si se genera dicha configuración).

Una vez compilado, el plugin puede ejecutarse en formato Standalone o cargarse como plugin con el formato generado durante la compilación VST3 compatible con la mayoría de programas de producción musical y sistemas operativos.
