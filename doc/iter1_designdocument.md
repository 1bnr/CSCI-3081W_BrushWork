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
characteristics common to each tool, along with sub-classes that handled specifics of each tool.  Below is a UML diagram that models the relationship we decided on.

![screen shot 2016-10-15 at 7 44 55 pm](https://media.github.umn.edu/user/5831/files/0136a68c-9310-11e6-9d11-ccb9a37700e7)

This figure shows the relationship between BrushWorkApp and our Tool class.  The multiplicity (listed on arrow between classes) is 1..* because we require BrushWorkApp to have at least 1 tool but no limit beyond that.  What is important in this figure is noticing that we have added a vector of tools, tool_list_.  All tools are stored here, and can be accessed with cur_tool_ (an integer value that can change based on which tool users click).  This was one of the first design decisions made by our team, it allows there to be an easy transition between tools and also keeps them stored together in memory.  Our group also added a member variable to BrushWorkApp, cur_color_.  This change allowed us to handle a tool's color as 1 object instead of passing it around as red/blue/green separately.  The code snippet below shows how cur_color_ is set, if cur_color_red_, cur_color_green_, or cur_color_blue_ are changed then cur_color_ will reflect that change.

![screen shot 2016-10-16 at 9 05 10 pm](https://media.github.umn.edu/user/5831/files/5a11b01a-93e4-11e6-9dd3-7bf42dbea4de)

The snippet below then shows how this simplified the function call to draw, we were able to use fewer arguments making the code easier to read and understand.

![screen shot 2016-10-15 at 1 58 58 am](https://media.github.umn.edu/user/5831/files/6979b3fa-927b-11e6-96bc-57a0ac84a059)

For our design we wanted to keep the tools as similar as possible, by creating a Tool class we were able to then require standards that every tool must have.  These were that all tools must have a mask, and that every tool must be able to draw. With a draw function defined in our Tool class this gave each of our sub-classes the ability to draw, only in special cases then would a tool ever need to override this method.  The last thing important to the design of the tool class was how to handle the mixing of colors as they are drawn to the canvas.  This happens when each tool is initialized and its mask is created.  When the mask is being created the proper float value is put into each vector element.  So when it comes to drawing onto the canvas, reading the mask can tell the tool with exactly how much intensity to draw. The figure below shows the set-up process for the highlighter's mask.  The highlighter needs to be somewhat transparent, and instructions asked for 40% current color and 60% what is in background.

![screen shot 2016-10-15 at 8 07 59 pm](https://media.github.umn.edu/user/5831/files/1f20cb42-9314-11e6-971e-21713c231d4d)

Within the second for-loop you will see each element of the mask being set to .4, this made sense to our group to include these "intensity levels" within the mask.  That way the mask wasn't only the shape being drawn to the canvas, but also held information on with what intensity the tool would draw to the canvas.

### 1.2 Design Justification

The main justification behind this design is its simplicity.  Our abstract tool class provides the groundwork for any tool a user may want to add, but also gives each tool the freedom to define a specific mask, blending technique, or drawing method.  The design also allows for a clear layer of abstraction, where each tool is merely a different set of requirements the program looks at before it draws to the canvas.  Our group thought it would be better not to force relations where they weren't needed.  Separating the tools even further into pens and other categories that are then sub-classes of Tool would be an example of that.  This to us seemed unnecessary, and almost clutters the abstraction.  In this case nothing is really gained from separating them, and it leads to extra source code/classes that don't offer significant change.  A big benefit to this design is how easy it can be to add new tools, defining a mask is really all it comes down to.  With other designs you may end up creating three or four separate objects for each instantiation of a tool, with ours all it requires is 1 call to that tool and everything can be created from it.  That is why we included the mask within our tool class, and not as its own class.  It makes it a lot easier for users to instantiate a tool when that class handles the creation of its own attributes and data.  Lastly, the major benefit to our design is its usability.  By creating an overridable draw method in our Tool class, when changes needed to be made they could be made in one place.  If a specific tool's mask needed to be changed or experimented with, those changes only had to be made in one place.  It goes back to the first point brought up that our Tool class provides the groundwork but leaves freedom to each tool to be different.  This was what we based our design upon, and it led to simple relationships between classes that directly modeled the real world.

## 2  Design Question Two
> Unlike most of the tools, the Eraser returns the canvas to its original color. One of the challenges in this iteration is giving the eraser the authority or information required to have this effect while having minimal impact on the way the rest of the tools are defined.
> First, in the **Design Description** section below, describe the design you developed to address this challenge.  Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 2.1 Design Description
Instead of trying to differentiate the eraser from the other tools, our group wanted to keep it as similar as possible.  Our design relied on the fact that every time our draw function was called, it was passed cur_color_ as an argument.  For eraser, all that changed was the color passed to draw happened to be the background color.  In this sense our abstraction didn't have to be ruined, and other classes didn't need to be changed so eraser could have this ability.  Within brushwork app, when the init function is called a color is passed that is set as the background color.  All we did was simply create a new variable that stored this exact same information.  The figure below shows the creation of the variable that stores the background color.

![screen shot 2016-10-17 at 12 19 51 am](https://media.github.umn.edu/user/5831/files/88e4f134-93ff-11e6-908b-c2397feefde5)

Having the background color stored means that now technically any tool can have access to it if needed.  Our group thought this was important because in the future a new tool may need to be added that also needs to access the background color.  The figure below then shows how if users click to use the eraser, cur_color is set to be background_color_. This means when our draw function is called the eraser will appear to be "erasing" but all its really doing is drawing with the background_color.

![screen shot 2016-10-17 at 12 24 02 am](https://media.github.umn.edu/user/5831/files/23c4aa1e-9400-11e6-9302-a5408135f3c4)


### 2.2 Design Justification

To us it was important that our functions/classes didn't have to change just because the eraser had special requirements.  That is why we chose to instead set cur_color_ to background_color_ when the eraser was in use.  This seemed to be the easiest solution, but also the smartest because it opens up the door for other tools.  Now any new tools added can also access the background color if needed, so this design is beneficial for future updates/changes.  But it also helps in another scenario, and that's if the background color changes.  Say a future update allows the ability for a user to change the background color mid drawing.  Our design allows for the eraser to always have the current background_color_, and this was also a reason we saw this design decision fit.  The design we chose didn't just solve the problem for now, it solved many future problems by making the code flexible and realistic.

## 3  Design Question Three
> A new developer on your team must add a new tool to BrushWork. This tool is called  _Pencil._ This tool is a single, non-transparent pixel that completely replaces the existing colors on the canvas in the same way as the pen or calligraphy pen blend.  
> Describe in the form of a tutorial (including code snippets) exactly what changes would need to be made to your program in order to fully integrate this new tool.

### Programming Tutorial: Adding a New Pencil Tool to BrushWork

The first step that needs to be taken is adding a header and source file for the new Pencil class.  This will look very similar to the other tool classes, the easiest files to use as a guide would be pen.h/pen.cc.  The figure below shows a section of pen.h, and following this format will help to create pencil.h.  Looking at the four include statements at the top of the figure, these same include statements will be needed in pencil.h.  Now turning to the class definition within pen.h, pencil will look very similar but "Pencil" will need to be substituted where "Pen" is used.

![screen shot 2016-10-18 at 8 35 07 pm](https://media.github.umn.edu/user/5831/files/2761997e-9573-11e6-9adc-dce9bf3a2fa9)

This should be all that is needed for pencil.h.  Now the source file needs to be created and this will be modeled from pen.cc.  Just like in pen.cc an include statement must be used that includes pencil.h, so at runtime these files can be linked.  Most of the other tools have more complicated masks, so these masks are generated when the tool is initialized as seen below in a snippet from pen.cc.  In the case of pencil rows/cols would be set to 1 because the pencil has a mask that is a single pixel.  Since it's such a simple mask it can be hard-coded in. Then just like in the figure, set_tool_mask(mask) must be called to set the mask that you created to the tool's private member variable tool_mask_.

![screen shot 2016-10-18 at 8 49 32 pm](https://media.github.umn.edu/user/5831/files/e2754160-9574-11e6-80ea-121e698707ce)

Now both header file and source file have been created, but one more include statement must be used.  The figure below shows the include statements from brushwork_app.h, pencil.h will need to be added to this section also.  Thereby linking the new Pencil class with BrushWorkApp, and allowing a Pencil tool to be initialized within the file.

![screen shot 2016-10-18 at 8 55 11 pm](https://media.github.umn.edu/user/5831/files/5d1c0a98-9575-11e6-9604-0d8a9922d33f)

The next step is to initialize a pencil and place it into tool_list_, our vector of tools.  The snippet below is from brushwork_app.cc, and it shows the initTools function , in specific the creation of tools and their addition to tool_list_.  This same approach can be used to create a pencil, and then store it in our vector of tools.

![screen shot 2016-10-18 at 10 03 30 pm](https://media.github.umn.edu/user/5831/files/e34e6efe-957e-11e6-8b1d-32f94cd2d832)

Now that a pencil tool has been created, functionality needs to be added so when pencil draws to the canvas it draws with the currently selected color.  This happens within brushwork app's display function.  Below is a snippet from brushwork_app.cc that shows the display function.  Notice how many cases exist, for example eraser is given a special case because it's current color is actually the background color.  In this case the pencil will function just like the pens and highlighter, therefore a new case can be added that falls through to case 0 (pen's case).  The case number will be the index that pencil is stored at in tool_list_.

![screen shot 2016-10-19 at 12 14 16 am](https://media.github.umn.edu/user/5831/files/a8233ac2-9591-11e6-945b-a584246dd637)


Lastly, an interface button must be created so Pencil is added to the options window.  When this is done users can click the button and the currently selected tool will be changed to a pencil.  To do this go into brushwork_app.cc and the InitGlui function, the figure below shows the code that will be important to look at.  Just like the others create a new radio button labeled with "Pencil".

![screen shot 2016-10-19 at 12 21 08 am](https://media.github.umn.edu/user/5831/files/1d89d4ec-9592-11e6-9e58-c31368cf30a5)

If all this is done correctly, you should have a fully functioning pencil tool.
