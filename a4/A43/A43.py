#!/usr/bin/env python3

"""import the function and class in the A42"""
from A42 import *
"""import the function and class in the A41"""
from A41 import * 
print(__doc__)

class giftCard:
    def __init__(self, file_name:str, card_title:str) -> None:
        self.file_name = file_name
        self.card_title = card_title

    def GenCards(self, length:int, height:int, drawing_number:int):
        '''Here is for generate cards'''

        f:IO[str] = open(self.file_name, "w")
        web = HTMLdoc
        web.writeHTMLHeader(f, self.card_title)
        openSVGcanvas(f, 1, (length, height))
        for count in range(drawing_number):
            drawing = ArtConfig(drawing_number, length, height)
            if(drawing.SHA == 0):
                cir = Circle
                cir.drawCircleLine(f, 2, Circle((drawing.X, drawing.Y, drawing.RAD), (drawing.R, drawing.G, drawing.B, drawing.op)))
            elif(drawing.SHA == 1):
                rect = Rectangle
                rect.drawRectangleLine(f, 2, Rectangle((drawing.X, drawing.Y, drawing.W, drawing.H), (drawing.R, drawing.G, drawing.B, drawing.op)))

        web.closeSVGcanvas(f, 1)
        f.close

    def __repr__(self):
        return "card(%r, %r)" % (self.card_title, self.file_name)

def main():
    card = giftCard( "A4_part3.html", "Gift Card")
    card.GenCards(1000, 500, 1000)

if __name__ == '__main__':
    main()