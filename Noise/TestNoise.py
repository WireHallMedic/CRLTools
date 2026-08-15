from ctypes import *
import os
import tkinter


noise = cdll.LoadLibrary("./Noise.dll")
noise.initialize.argtypes = [c_long]
noise.initialize.restype = c_int
noise.getNoiseValue.argtypes = [c_double, c_double]
noise.getNoiseValue.restype = c_double
noise.getChoirValue.argtypes = [c_double, c_double]
noise.getChoirValue.restype = c_double

class TestNoise(tkinter.Frame):
   
   def __init__(self, master):
      """Initialize frame and components."""
      super(TestNoise, self).__init__(master)
      master.title("Noise Test")
      
      self.displaySize = 500
      
      noise.initialize(123456789)
      if noise.validateArrays() == 1:
         print("Bad arrays");
         exit(0);
      else:
         print(noise.validateArrays());
      print(type(noise.getNoiseValue(1.5, 1.5)))
      # make the canvas
      self.canvas = tkinter.Canvas(master, width = self.displaySize + 200, height = self.displaySize + 100)
      self.canvas.pack()
      self.paint()

   def getGreyString(self, val):
      """
      Return a three-item tuple of the desired grey's color value for RGB calls
      """
      val = int(val * 256)
      val = "{:02x}".format(val)
      return ('#' + val + val + val)
      
   
   def paint(self):
      """
      Paint the canvas, depending on what was passed.
      Broken apart a bit for readability.
      Drawn at *2 size
      """
      # pixel setting loop
      for x in range(self.displaySize // 2):
         for y in range(self.displaySize // 2):
            # limit how often we're calculating positions
            xx = x * 2
            yy = y * 2
            # generate the grey value as a tuple
            noiseVal = noise.getNoiseValue(x * .03, y * .03)
            print(noiseVal);
            greyStr = self.getGreyString(noiseVal)
            # set four pixels
            #_ = self.canvas.create_rectangle(xx, yy, xx + 1, yy + 1, fill = greyStr, outline = greyStr)
            
      # request screen update rather than waiting
      self.canvas.update_idletasks()

if __name__ == "__main__":
   TestNoise(tkinter.Tk())