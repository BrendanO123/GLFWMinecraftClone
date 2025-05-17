import java.io.*;
import javax.imageio.*;
import java.awt.image.*;
import java.awt.*;
import java.util.*;
import java.math.*;

@SuppressWarnings("unused")
public class Resizer{
    
    public static void main(String[] args){

        int xBound = 256; int yBound = 64; 
        int singleXBound = 16; int singleYBound = 16;
        File spriteMap = new File("MinecraftClone/assets/sprites/BlockMap/block_map.png");
        
        File block = new File("MinecraftClone/assets/sprites/Dark_Oak_Log.png");
        int posX = 11; int posY = 0;
        int originalXSize = 160; int originalYSize = 160;
        
        BufferedImage map = new BufferedImage(xBound, yBound, BufferedImage.TYPE_INT_ARGB), temp = new BufferedImage(originalXSize, originalYSize, BufferedImage.TYPE_INT_ARGB);
        try{
            map = ImageIO.read(spriteMap);
            temp = ImageIO.read(block);
        }
        catch(IOException e){e.printStackTrace(); System.exit(-1);}

        for(int x=0; x<singleXBound; x++){
            for(int y=0; y<singleYBound; y++){
                map.setRGB(x+posX*singleXBound, yBound-(posY+1)*singleYBound+y, temp.getRGB(x*originalXSize/singleXBound, y*originalYSize/singleYBound));
            }
        }

        try{ImageIO.write(map, "png", spriteMap);}
        catch(IOException e){e.printStackTrace(); System.exit(-1);}
    }
}