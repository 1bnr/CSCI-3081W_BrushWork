# Design Justifications for FlashPhoto
#### Group Name:
Group 0x07

#### Members:
- Abner Holsinger
- Isaac Schwab
- Ben Bramanti

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
For the filters our group decided it would be best to implement each filter as its own class.  We decided we would not differentiate too much between pixel-independent/convolution-based filters, and this led to easily defined filters which only required a single method to apply the filter.  Below is a UML diagram that models our groups idea, Threshold is the only filter included in the diagram but imagine that any of our other filters could take its spot and the relationships would still hold.

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

No base classes were used for our design, each filter has its own class which defines an apply_filter method that follows the filter requirements.  If a filter used a kernel it was instantiated and regenerated all within the apply_filter method, similar to our first iteration solution where we had each tool initializing its mask within it's constructor.

### 1.2 Design Justification
When first trying to tackle these filters, our group thought the best idea would be to have a base filter class, here rules would be set in place for what a filter can and cannot do.  When we started implementing this, it almost seemed more of a hassle than it was worth, what we decided on was our current design.  We left out any base class, and instead gave each filter its own separate class where it could define how it would apply its filter.  We stuck with this decision because it required less files (no files needed for base class) and ultimately these filters were relatively simple and we didn't want to confuse the matter with a hard to follow inheritance structure.  One thing our group also thought of was picturing the filter as a function that operated on a pixel buffer, and more or less that is what we did.  Since we made our apply_filter method static, we did not ever have to instantiate a filter, this was one thing our group saw as a big benefit to our design.  We did not have to waste any extra memory to instantiate a filter for a one time use, instead we could just operate in place on a pixel buffer.

Our design handled the pixel-independent filters very well, but it got a little more complicated when it came to the convolution-based filters.  The same structure was used where each convolution-based filter had its own class where it could define an apply_filter method that met the filter's requirements.  Our team decided to generate kernels within this method, and in the end this was a bit larger of a task than we expected.  It really complicated our apply_filter method to be generating and possibly re-generating kernels all within the same method.  This was a downside to our design because a kernel class might have been very efficient in this case.  We could have had methods created in that class to quickly re-size kernels and pass them back to our apply_filter method.  But the positive side of our design was everything regarding a filter can be found in a single class, for users they do not have to be searching around multiple files trying to figure out how a given filter operates.  Really all a user has to look at is the filter's apply_filter method and that would give any information that is needed.  For that reason our team liked this design because it kept all details regarding a filter inside of one class.


## 2  Design Question Two
> One common software feature included in this iteration is the undo/redo mechanic, where any modification to the canvas can be reversed, and then optionally re-applied.
> First, in the **Design Description** section below, describe the design you developed to address this challenge.  Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 2.1 Design Description
Our team decided to implement the undo/redo mechanic using a vector of PixelBuffer pointers called states_ and an int of the current state called cur_state_. We declare both states_ and cur_state_ as private member variables within the flashphoto_app.h file. We decided to imagine that states_ would behave similar to a stack, in that there would be a beginning and an end. We would then modify the current position of the stack by simply incrementing or decrementing the cur_state_ index. The idea is that decrementing cur_state_ by 1 would correlate to undo, and incrementing by 1 would redo. We also decided that we want to save the state of stack right before we modify the canvas. This functionality sets up how we handle the rest of the implementation of undo/redo.
The code snippet below shows the actual declaration of states_ and cur_state_.
![screen shot 2016-11-19 at 3 52 10 pm](https://media.github.umn.edu/user/5833/files/3d4e6daa-ae70-11e6-8fd8-bee437882073)

To handle the functionality of adding PixelBuffer pointers to states_ and maintaining states_ we created the functions add_buffer_to_undo_stack() and maintain_states_stack().

In the code snippet below you can see the add_buffer_to_undo_stack() function. The purpose of this function is to add the state of the program to the states_ stack. It will be called before any action that modifies the display_buffer_. This function takes a PixelBuffer*. All calls to this function will pass display_buffer_ as the parameter because display_buffer_ is always what is currently drawn to the canvas. We then create a copy of current_buffer (display_buffer_) called old_buffer that will hold the current state of the screen when the function was called. Now we simply just use the built in vector function push_back() to add this copy to the end of our states_ stack. After pushing, we increment the
cur_state_ index so that we are at the correct position in the stack and then set the current_buffer pointer to the
states_[cur_state] pointer. The last part of the function is to check if the undo toggle should be enabled. At the end of the function the application has now successfully saved the current display_buffer_ and any new operations can be drawn to the screen.
![screen shot 2016-11-19 at 5 16 43 pm](https://media.github.umn.edu/user/5833/files/070f6cb0-ae7c-11e6-8ad4-ef4710fa41fc)

The purpose of the maintain_states_stack() function is to handle the case in which the user has clicked undo and then modifies the canvas in some way. When this occurs all changes that had been undid to that point should be erased, but previous states should stay intact. The code snippet below shows how we implemented this. The case in which we need to erase from the states_ stack will only occur if the cur_state_ is not at the end of the stack. The if statement checks this case. If we do need to delete, we use the built in vector function erase(). We erase everything from after the current state to the end of the stack. At this point the user now can no longer redo, so we disable the redo toggle.
![screen shot 2016-11-19 at 5 16 55 pm](https://media.github.umn.edu/user/5833/files/07180924-ae7c-11e6-9ab4-b2ea3a5d165b)

The second fundamental part of the undo/redo design is the StateManager class. While this function was provided in support code, it was up to us to determine how we would implement the functionality. We decided that the functions UndoOperation() and RedoOperation() would be called to switch the application PixelBuffer* display_buffer_ to a saved PixelBuffer* state in the states_ stack. As described at the beginning of this section, we wanted that to be as simple as incrementing or decrementing cur_state_ by 1.

The code snippet below shows how we implemented this functionality. Because add_to_undo_stack() and maintain_states_stack() correctly build and maintain the states_ stack and the cur_state_ index all we need to do is modify which states_ PixelBuffer*  display_buffer_ is set to. As you can see in the code we pass in the needed parameters and then set them according to either the previous or next index in states_.
![screen shot 2016-11-19 at 7 05 10 pm](https://media.github.umn.edu/user/5833/files/26943976-ae8b-11e6-90ce-0afd82a4c1ee)

The last part of our design for undo/redo is how we actually call these functions. Any action that modifies the screen (tools, filters, loading images), we make our calls to add_buffer_to_undo_stack() and maintain_states_stack(). The code snippet below is an example of how we handle states_ when a filter is to be applied to the screen.
![screen shot 2016-11-19 at 7 12 52 pm](https://media.github.umn.edu/user/5833/files/3cac6ade-ae8c-11e6-97fe-6292b4ac62f5)

### 2.2 Design Justification
Our group thought of a couple different ways to implement the undo/redo functionality. The main topics we discussed were: which structure to use for the stack, what to store in the stack, and how to handle calls to undo/redo functions.

For the data structure we talked about a few options such as: standard arrays, linked lists, and vectors. We decided on vectors due to the pros they had over the other options. The c++ std::vector template allows for dynamic allocation, which is perfect for this application because our stack of states could be growing or shrinking. The other advantage of vectors is that they were already defined and had many of the functions we needed, such as erase() and push_back() already built. If we had gone with a linked list type structure we would have had to build it ourselves.

The next challenge of our design was how we wanted to store our states. The first idea was to just store PixelBuffer objects. The initial thought was this would simplify the undo/redo module because we wouldn't need to worry about pointers. However, after actually implementing a vector of PixelBuffers we ran into some issues. The biggest being that our canvas wouldn't resize correctly when images were loaded to the screen. We determined that this error had to do with our PixelBuffer objects not correctly passing the height and width parameters. Thus, we looked into the other option we had discussed, which was storing PixelBuffer pointers in our states_ vector. This solution was chosen based on the fact that it solved the bugs we were having with the other implementation. In a way it did unify the application due to the fact that the main display_buffer_ was a PixelBuffer*.

The last big discussion point of the undo/redo design was how we were going to handle calls to our various functions. We really had two options, do we call our functions before we modify the canvas, or after. There was even a discussion in lecture about this topic. When it came down to it we decided that either way would work as long as we stuck with our choice throughout the implementation. When actually implementing it we decided that any action that would modify the canvas would first call our functions add_buffer_to_undo_stack() and maintain_states_stack().

A few other minor design decisions we discussed were where we actually wanted to handle switching the current buffer. The most obvious option was use the StateManager class and functions that were provided in the support code. However, while implementing the functionality it became obvious that if we wanted to we could handle everything in the FlashPhotoApp class. We decided that even though doing this would potentially be easier, it would be better to go with the StateManager class that was provided. The FlashPhotoApp class already had so much going on it so using a separate class helped keep the code cleaner and easier to read.

Overall we are happy with the design and functionality of our Undo/Redo Mechanic.


## 3  Design Question Three
> A new developer on your team must add a new filter to FlashPhoto. This filter is called  _Invert._ This filter performs the following conversion to all pixels in the canvas:
> ```
> newColor's red   = 1 - oldColor's red
> newColor's green = 1 - oldColor's green
> newColor's blue  = 1 - oldColor's blue
> ```
> Describe in the form of a tutorial (including code snippets) exactly what changes would need to be made to your program in order to fully integrate this new filter.

Step 1:
This filter will fall under the category of pixel-independent filters, so the tutorial will be based around looking at the threshold class and building something very similar to it that handles inverting colors.  The first step will be to create a header file invert.h, this will look very similar to threshold.h with one small change.  The invert filter only needs to be passed a pixel buffer pointer, it has no need for any extra arguments like thresh_amount.  The figure below shows a snippet of threshold.h, when writing invert.h the arguments to apply_filter should just be a pixel buffer pointer.

![screen shot 2016-11-19 at 8 48 53 pm](https://media.github.umn.edu/user/5831/files/e7c34228-ae99-11e6-8268-38588dda72ae)

Step 2:
Make sure to include invert.h within filter_manager.h, better to do it now before you forget and compile!  Below is a snippet from filter_manager.h that shows the include statements, one should be added for invert.h.

![screen shot 2016-11-19 at 8 52 28 pm](https://media.github.umn.edu/user/5831/files/52f8f54c-ae9a-11e6-9444-bf8e9b82bcde)

Step 3:
Now that the header file has been created, it is time to write the implementation details into invert.cc.  This file can be modeled from threshold.cc but remember apply_filter should have just a single argument.  The structure of apply_filter can stay very similar, the only things that need to be changed are the conditionals within the for loop.  Below is a snippet from threshold.cc, it shows the conditional statements, this is the only section that needs changing.  The inverting process is very simple and does not require any conditionals.  Within the nested for-loop you should set each of the new colors (new_red,new_green,new_blue), to be one minus the original color at that pixel.  To get the original color at that pixel you can use the same operations that are seen in the snippet below, set_pixel() and red()/blue()/green().  To set these new colors it is as simple as new_red = 1 - (p->get_pixel(i,j).red()).  This same format can be used to set new_blue and new_green.

![screen shot 2016-11-19 at 9 02 19 pm](https://media.github.umn.edu/user/5831/files/7f399df4-ae9b-11e6-844c-c639b7b62193)

Step 4:
Both invert.h and invert.cc have been created, so it is time to actually create calls to this filter within the app.  Within filter_manager.h you will need to write a new method ApplyInvert, it will look the same as all of the other methods already written in that file.  Below is a snippet from filter_manager.h that shows the ApplyThreshold method, make a new one for ApplyInvert.

![screen shot 2016-11-19 at 9 04 49 pm](https://media.github.umn.edu/user/5831/files/38b2988a-ae9c-11e6-852c-51caa519f3d7)

Now you will have to go into filter_manager.cc and write the details of what this method will do.  Below is a snippet from filter_manager.cc that shows the ApplyThreshold method, you will need to write the implementation details for ApplyInvert.  Remember it should look just like the ApplyThreshold method, but in this case will call Invert's apply_filter method statically.  What you are doing in this step is writing a method that will actually apply the filter.

![screen shot 2016-11-19 at 9 09 34 pm](https://media.github.umn.edu/user/5831/files/82c3442e-ae9c-11e6-89b1-0560ffd64aad)

Step 5:
You have written the header/implementation details for invert, and also created a method that will apply the filter.  Now you need to actually make the call from flashphoto_app.cc.  Looking at this file there is a long list of cases for each different filter you can apply, below shows the code written for the threshold filter.  You will need to create a new case that handles when a user clicks to use the invert filter.  It should look the same as the code below but obviously call ApplyInvert instead of ApplyThreshold.

![screen shot 2016-11-19 at 9 12 07 pm](https://media.github.umn.edu/user/5831/files/6570a492-ae9d-11e6-88a0-9e64b957d075)

If these steps are executed properly you should now have a fully functioning invert filter.
