# Design Justifications for FlashPhoto
#### Group Name:
<Group 0x07>

#### Members:
- <Abner Holsinger>
- <Isaac Schwab>
- <Ben Bramanti>

#### Instructions
> Respond to each of the design questions below.  Make your answers factual and compelling.  Where appropriate, reference alternative designs you considered, code snippets, and diagrams within your writing in order to be clear and back up your claims.  As we have discussed in class, when writing with reference to figures make sure to tell the reader what to look for in the diagram or what exactly you want the reader to notice in the code snippet.  Remember that the design of your project is worth 1/3 of the total project grade.  Also remember that when grading the design portion of the project, this design justification document is the only thing we will look at.  This document must stand on its own.  Rather than linking to your actual code, carefully pick the most important code snippets from your project to include here in order to provide convincing detail for your answers to the questions below.  
> A few tips to maximize the success of your design document:  
>   1. Make sure the **description** of your design decision only contains an objective description of how you structured your design and how it was implemented (specifically how your solution solves the problem given in the prompt). Save any arguments in favor of your design for the **justification** section.
>
>   2. Your justification will probably need to compare against at least one alternative, and you will need to provide a compelling argument for why your solution is better than the alternative.
>
>   3. Edit this file when writing your design document. Do not move or rename this file. Do not direct to any outside resources for your images or code. Place all images and code in this document. Please match the formatting of the [Example Design Document](https://github.umn.edu/umn-csci-3081F16/Example-Design-Document/blob/master/doc/DesignDocument.md) and [its source](https://raw.github.umn.edu/umn-csci-3081F16/Example-Design-Document/master/doc/DesignDocument.md?token=AAADyd5L8wd57F_qLX4Nf-2nVvfRlMj5ks5YH-qHwA%3D%3D) as precisely as possible, especially in regards to:
>     - **Formatting code** (do not include images of your code, make sure that your code is formatted with C++ coloring)
>     - **Inserting images**
>     - **Numbered lists for your tutorial**
>     - **Captioning your Figures**
>     - **Including the original prompts in their original quote form**  
>
>  This formatting helps us grade your assignments effectively, and thus failure to meet these requirements may result in point deductions. Any material that is not presented in this design document will not be graded.
>   4. When including a class diagram, only show the classes and members that convey the point you're trying to make. For example, showing the class BaseGfxApp in a UML diagram will probably not be appropriate.





## 1  Design Question One
> This iteration of the project introduces the concept of filters. You had to implement several filters, which fell into two types: pixel-independent (where each pixel is filtered independently), and convolution-based (where filtering a pixel requires information about its neighboring pixels by means of a kernel). Naturally, a key design decision is how these filters are represented. Each filter has a different algorithm for modifying the canvas, and only some of these algorithms require kernels.
> First, in the **Design Description** section below, describe the design you developed to address this challenge. We expect that you will include at least one figure showing the relationships of the classes affected by your design. Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 1.1 Design Description
For the filters our group decided it would be best to implement each filter as its own class.  We decided we would not differentiate too much between pixel-independent/convolution-based filters, and this led to very easily defined filters which only required a single method to apply the filter.  Below is a UML diagram that models our groups idea, Threshold is the only filter included in the diagram but imagine that any of our other filters could take its spot and the relationships would still hold.

![screen shot 2016-11-19 at 3 47 30 pm](https://media.github.umn.edu/user/5831/files/d23f62e8-ae89-11e6-9526-4695ed51384a)

What is important to note is that each filter has an apply_filter method, this method is passed a pointer to a pixel buffer that it will then apply the filter to.  This method makes a copy of the pixel buffer, and one by one sets each individual pixel of the copy following the requirements of the filter.  After the whole canvas has been iterated through the original pixel buffer pointer is then set to point to the new filtered copy.  The first figure below shows the copy of the passed in pixel buffer being created, and the second shows the re-pointing to the new filtered buffer.

![screen shot 2016-11-19 at 6 59 39 pm](https://media.github.umn.edu/user/5831/files/cd3b0576-ae8a-11e6-9f9f-4eb921492d65)

![screen shot 2016-11-19 at 6 59 51 pm](https://media.github.umn.edu/user/5831/files/d7dfd47a-ae8a-11e6-85af-9f54672d0d6d)

Both types of filters use this logic within their apply_filter method.  The only difference is that convolution-based filters also instantiate a kernel in the apply_filter method.  Below is a figure that shows the kernel being created for our edge detect filter.

![screen shot 2016-11-19 at 7 07 15 pm](https://media.github.umn.edu/user/5831/files/937baaba-ae8b-11e6-8b63-6fc487f6cb6b)

Within the method the kernel may have to be regenerated when looking at a pixel that is right on the border of the canvas.  For this case our kernel was regenerated so the filter applied properly, this was all done inside the apply_filter method.  Looking back at the UML diagram above you can see that filter manager has an ApplyThreshold method, our group decided that when this method was called the filter should then be applied.  Below is a picture of the implementation details for the ApplyThreshold method, you can see that we didn't actually have to instantiate a Threshold object because our apply_filter method was static.

![screen shot 2016-11-19 at 7 17 44 pm](https://media.github.umn.edu/user/5831/files/e6a66350-ae8c-11e6-93aa-b92024ef7ce9)

Lastly, note that display_buffer_ is always what we are passing to a filter, this way when we click to apply a filter it grabs the current canvas and applies the filter to that, below is a snippet from flashphoto_app.cc that shows a call being made to the filter manager.  Looking at the argument passed to ApplyThreshold you will see that it is the display_buffer_.

![screen shot 2016-11-19 at 7 21 34 pm](https://media.github.umn.edu/user/5831/files/9f5cf42c-ae8d-11e6-8ee4-5f66fe9c1fe1)

No base classes were used for our design, each filter has its own class which defines an apply_filter method that follows the filter requirements.  If a filter used a kernel it was instantiated and regenerated all within the apply_filter method, similar to our first iteration solution  where we had each tool initializing its mask within it's constructor.

### 1.2 Design Justification
When first trying to tackle these filters, our group thought the best idea would be to have a base filter class, here rules would be set in place for what a filter can and cannot do.  When we started implementing this, it almost seemed more of a hassle than it was worth, what we decided on was our decision.  We left out any base class, and instead gave each filter its own separate class where it could define how it would apply its filter.  We stuck with this decision because it required less files (no files needed for base class) and ultimately these filters were relatively simple and we didn't want to confuse the matter with a hard to follow inheritance structure.  One thing our group also thought of was picturing the filter as a function that operated on a pixel buffer, and more or less that is what we did.  Since we made our apply_filter method static, we did not ever have to instantiate a filter, this was one thing our group saw as a big benefit to our design.  We did not have to waste any extra memory to instantiate a filter for a one time use, instead we could just operate in place on a pixel buffer.

Our design handled the pixel-independent filters very well, but it got a little more complicated when it came to the convolution-based filters.  The same structure was used where each convolution-based filter had its own class where it could define an apply_filter method that met the filter's requirements.  Our team decided to generate kernels within this method, and in the end this was a bit larger of a task than we expected.  It really complicated our apply_filter method to be generating and possibly re-generating kernels all within the same method.  This would be a downside to our design because a kernel class might have been very efficient in this case.  We could have had methods created in that class to quickly re-size kernels and pass them back to our apply_filter method.  But the positive side of our design was everything regarding a filter can be found in a single class, for users they do not have to be searching around multiple files trying to figure out how a given filter operates.  Really all a user has to look at is the filter's apply_filter method and that would give any information that is needed.  For that reason our team liked this design because it kept all details regarding a filter inside of one class.


## 2  Design Question Two
> One common software feature included in this iteration is the undo/redo mechanic, where any modification to the canvas can be reversed, and then optionally re-applied.
> First, in the **Design Description** section below, describe the design you developed to address this challenge.  Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 2.1 Design Description

### 2.2 Design Justification


## 3  Design Question Three
> A new developer on your team must add a new filter to FlashPhoto. This filter is called  _Invert._ This filter performs the following conversion to all pixels in the canvas:
> ```
> newColor's red   = 1 - oldColor's red
> newColor's green = 1 - oldColor's green
> newColor's blue  = 1 - oldColor's blue
> ```
> Describe in the form of a tutorial (including code snippets) exactly what changes would need to be made to your program in order to fully integrate this new filter.

### Programming Tutorial: Adding a New Pencil Tool to FlashPhoto

1. <Step 1>
2. <Step 2>
<etc>
