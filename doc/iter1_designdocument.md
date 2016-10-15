# Design Justifications for BrushWork
#### Group Name:
Group 0x07

#### Members:
- Abner Holsinger
- Isaac Schwab
- Ben Bramanti

#### Instructions
> Respond to each of the design questions below.  Make your answers factual and compelling.  Where appropriate, reference alternative designs you considered, code snippets, and diagrams within your writing in order to be clear and back up your claims.  As we have discussed in class, when writing with reference to figures make sure to tell the reader what to look for in the diagram or what exactly you want the reader to notice in the code snippet.  Remember that the design of your project is worth 1/3 of the total project grade.  Also remember that when grading the design portion of the project, this design justification document is the only thing we will look at.  This document must stand on its own.  Rather than linking to your actual code, carefully pick the most important code snippets from your project to include here in order to provide convincing detail for your answers to the questions below.


## 1  Design Question One
> This iteration of the project is all about tools. Naturally, a key design decision is how these tools are represented. Each tool has several characteristics, including the shape of the tool, its size, and the way it blends with the canvas when the tool is applied. Some tools share characteristics with other tools, such as how the pen and calligraphy pen tools blend with the canvas in the same manner.
> First, in the **Design Description** section below, describe the design you developed to address this challenge. We expect that you will include at least one figure showing the relationships of the classes affected by your design. Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 1.1 Design Description
Looking at the requirements for this iteration, our group knew each tool will differ from the others but
may also share some features in common.  In terms of design this meant developing a Tool class, that could offer
characteristics common to each tool, along with sub-classes that handled specifics of each tool.  Below are two figures
both of which are UML diagrams.  The figures are from the same diagram, they are just focused on different areas.

![screen shot 2016-10-15 at 1 16 15 am](https://media.github.umn.edu/user/5831/files/49922964-927b-11e6-8207-800b677bec0b)


![screen shot 2016-10-15 at 2 01 54 am](https://media.github.umn.edu/user/5831/files/6388af96-927b-11e6-8efc-384f89fe1540)

The first figure shows the relationship between BrushWorkApp and our Tool class.  The multiplicity (listed on arrow between classes) is 1..* because we require BrushWorkApp to have at least 1 tool but no limit beyond that.  What is important in this figure is noticing that we have added a vector of tools, tool_list_.  All tools are stored here, and can be accessed with cur_tool_ (an integer value that can change based on which tool users click).  This was one of the first design decisions made by our team, it allows there to be an easy transition between tools and also keeps them stored together in memory.  Our group also added a member variable to BrushWorkApp, cur_color_.  This change allowed us to handle a tool's color as 1 object instead of passing it around as red/blue/green separately.  The code snippet below shows how cur_color_ is set, if cur_color_red_,cur_color_green_,or cur_color_blue_ are changed then cur_color_ will reflect that.
![screen shot 2016-10-15 at 1 46 41 am](https://media.github.umn.edu/user/5831/files/66f634c8-927b-11e6-9b3b-5df4f910d0d7)
The snippet below then shows how this simplified the function call to draw, we were able to use fewer arguments making the code easier to read and understand.

![screen shot 2016-10-15 at 1 58 58 am](https://media.github.umn.edu/user/5831/files/6979b3fa-927b-11e6-96bc-57a0ac84a059)

### 1.2 Design Justification


## 2  Design Question Two
> Unlike most of the tools, the Eraser returns the canvas to its original color. One of the challenges in this iteration is giving the eraser the authority or information required to have this effect while having minimal impact on the way the rest of the tools are defined.
> First, in the **Design Description** section below, describe the design you developed to address this challenge.  Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 2.1 Design Description

### 2.2 Design Justification


## 3  Design Question Three
> A new developer on your team must add a new tool to BrushWork. This tool is called  _Pencil._ This tool is a single, non-transparent pixel that completely replaces the existing colors on the canvas in the same way as the pen or calligraphy pen blend.  
> Describe in the form of a tutorial (including code snippets) exactly what changes would need to be made to your program in order to fully integrate this new tool.

### Programming Tutorial: Adding a New Pencil Tool to BrushWork

1. <Step 1>
2. <Step 2>
<etc>
