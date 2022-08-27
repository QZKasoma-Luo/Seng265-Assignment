#!/usr/bin/env python
"""Assignment 4 Part 1 template"""

from turtle import circle
from typing import IO


class Circle:
    """Circle class"""
    def __init__(self, cir: tuple, col: tuple) -> None:
        self.cx: int = cir[0]
        self.cy: int = cir[1]
        self.rad: int = cir[2]
        self.red: int = col[0]
        self.green: int = col[1]
        self.blue: int = col[2]
        self.op: float = col[3]
    
    def __repr__(self):
        return "circle(%r, %r)" % (self.cx, self.cy)
    
    def drawCircleLine(f: IO[str], t: int, self) -> None:
        """drawCircle method"""
        ts: str = "   " * t
        line1: str = f'<circle cx="{self.cx}" cy="{self.cy}" r="{self.rad}" '
        line2: str = f'fill="rgb({self.red}, {self.green}, {self.blue})" fill-opacity="{self.op}"></circle>'
        f.write(f"{ts}{line1+line2}\n")


class Rectangle:
    """Rectangle class"""
    def __init__(self, rec: tuple, col: tuple) -> None:
        self.x: int = rec[0]
        self.y: int = rec[1]
        self.length: int = rec[2]
        self.height: int = rec[3]
        self.red: int = col[0]
        self.green: int = col[1]
        self.blue: int = col[2]
        self.op: float = col[3]

    '''for drawing the Rectangle on the web'''
    def drawRectangleLine(f: IO[str], t: int, self):
        '''drawRectangle method'''
        ts: str = "   " * t
        line1: str = f'<rect x="{self.x}" y="{self.y}" width="{self.length}" height="{self.height}" fill="rgb({self.red}, {self.green}, {self.blue})" fill-opacity="{self.op}"/>'
        f.write(f"{ts}{line1}\n")

class HTMLdoc:
    """ProEpilogue class""" 
    def writeHTMLHeader(f: IO[str], winTitle: str) -> None:
        """writeHeadHTML method"""
        f.write(f"<html>\n")
        f.write(f"<head>\n")
        f.write(f"<title>{winTitle}</title>\n")
        f.write(f"</head>\n")
        f.write(f"<body>\n")
        
    def closeSVGcanvas(f: IO[str], t: int) -> None: 
        """closeSVGcanvas method"""
        ts: str = "   " * t
        f.write(f"{ts}</svg>\n")
        f.write(f"</body>\n")
        f.write(f"</html>\n")



def writeHTMLcomment(f: IO[str], t: int, com: str) -> None:
    """writeHTMLcomment method"""

    ts: str = "   " * t
    f.write(f"{ts}<!--{com}-->\n")

def openSVGcanvas( f: IO[str], t: int, canvas: tuple) -> None:
    """openSVGcanvas method"""
    ts: str = "   " * t
    writeHTMLcomment(f, t, "Define SVG drawing box")
    f.write(f'{ts}<svg width="{canvas[0]}" height="{canvas[1]}">\n')

def genRectArt(f: IO[str], t: int):
   '''genRectArt method'''
   rect1 = Rectangle
   rect2 = Rectangle
   rect3 = Rectangle
   rect4 = Rectangle
   rect5 = Rectangle

   rect1.drawRectangleLine(f, t, Rectangle((50,100, 50, 70), (100,70,100, 1)))
   rect2.drawRectangleLine(f, t, Rectangle((150,100, 70, 50), (100,60,100, 1)))
   rect3.drawRectangleLine(f, t, Rectangle((250,100, 80, 60), (60,57,100, 1)))
   rect4.drawRectangleLine(f, t, Rectangle((350,100, 63, 30), (100,50,100, 1)))
   rect5.drawRectangleLine(f, t, Rectangle((450,100, 70, 52), (52,35,100, 1)))



def genCircleArt(f: IO[str], t: int) -> None:
   """genART method"""
   circle1 = Circle
   circle2 = Circle
   circle3 = Circle
   circle4 = Circle
   circle5 = Circle
   circle6 = Circle
   circle7 = Circle
   circle8 = Circle
   circle9 = Circle
   circle10 = Circle 
   """drawing 10 different circles"""
   circle1.drawCircleLine(f, t, Circle((50,50,50), (255,0,0,0.5)))
   circle2.drawCircleLine(f, t, Circle((150,50,50), (255,0,0,0.5)))
   circle3.drawCircleLine(f, t, Circle((250,50,50), (255,0,0,0.5)))
   circle4.drawCircleLine(f, t, Circle((350,50,50), (255,0,0,0.5)))
   circle5.drawCircleLine(f, t, Circle((450,50,50), (255,0,0,0.5)))
   circle6.drawCircleLine(f, t, Circle((50,250,50), (0,0,255,0.5)))
   circle7.drawCircleLine(f, t, Circle((150,250,50), (0,0,255,0.5)))
   circle8.drawCircleLine(f, t, Circle((250,250,50), (0,0,255,0.5)))
   circle9.drawCircleLine(f, t, Circle((350,250,50), (0,0,255,0.5)))
   circle10.drawCircleLine(f, t, Circle((450,250,50), (0,0,255,0.5)))
   

def writeHTMLline(f: IO[str], t: int, line: str) -> None:
     """writeLineHTML method"""
     ts = "   " * t
     f.write(f"{ts}{line}\n")


def writeHTMLfile() -> None:
    """writeHTMLfile method"""
    fnam: str = "A41.html"
    winTitle = "A41"
    f: IO[str] = open(fnam, "w")
    web = HTMLdoc
    web.writeHTMLHeader(f, winTitle)
    openSVGcanvas(f, 1, (500,300))
    genCircleArt(f, 2)
    genRectArt(f, 2)
    web.closeSVGcanvas(f, 1)
    f.close()

def main() -> None:
    """main method"""
    writeHTMLfile()
    

if __name__ == "__main__":
    main()
 
