import java.io.*;
import javax.imageio.*;
import java.awt.image.*;
import java.awt.*;
import java.util.*;
import java.math.*;

@SuppressWarnings("unused")
public class Mipmaper{
    
    public static void main(String[] args){

        int xBound = 256; int yBound = 64; 
        int singleXBound = 16; int singleYBound = 16; int mipMapCount = 4;
        File spriteMap = new File("MinecraftClone/assets/sprites/BlockMap/block_map.png");

        File[] outMaps = new File[mipMapCount+1];
        for(int i = 0; i <= mipMapCount; i++){
            outMaps[i] = new File("MinecraftClone/assets/sprites/Levels/mapLevel" + i + ".png");
        }

        BufferedImage[] levels = new BufferedImage[mipMapCount+1];
        for(int i = 1; i <= mipMapCount; i++){
            levels[i] = new BufferedImage(xBound>>i, yBound>>i, BufferedImage.TYPE_INT_ARGB);
        }
        try{levels[0] = ImageIO.read(spriteMap);}
        catch(IOException e){e.printStackTrace(); System.exit(-1);}

        int xMax = xBound/2; int yMax = yBound/2; 
        final int byteMask = (1<<8)-1;
        final int AShift = 24;
        final int RShift = 16;
        final int GShift = 8;
        final int BShift = 0;

        for(int i = 1; i <= mipMapCount; i++){
            for(int x = 0; x < xMax; x++){
                for(int y = 0; y < yMax; y++){

                    int TL = levels[i-1].getRGB(2*x, 2*y); int TR = levels[i-1].getRGB(2*x+1, 2*y);
                    int BL = levels[i-1].getRGB(2*x, 2*y+1); int BR = levels[i-1].getRGB(2*x+1, 2*y+1);

                    float R, B, G; R = G = B = 0; int n = 0;
                    int RF, BF, GF, A=0;

                    if(((TL>>AShift) & byteMask)>0){
                        R += Math.pow((((TL>>RShift) & byteMask)/255.0f), 2.2f);
                        G += Math.pow((((TL>>GShift) & byteMask)/255.0f), 2.2f);
                        B += Math.pow((((TL>>BShift) & byteMask)/255.0f), 2.2f);
                        A = (((TL>>AShift) & byteMask) > A ? ((TL>>AShift) & byteMask): A); n++;
                    }
                    if(((TR>>AShift) & byteMask)>0){
                        R += Math.pow((((TR>>RShift) & byteMask)/255.0f), 2.2f); 
                        G += Math.pow((((TR>>GShift) & byteMask)/255.0f), 2.2f); 
                        B += Math.pow((((TR>>BShift) & byteMask)/255.0f), 2.2f); 
                        A = (((TR>>AShift) & byteMask) > A ? ((TR>>AShift) & byteMask): A); n++;
                    }
                    if(((BL>>AShift) & byteMask)>0){
                        R += Math.pow((((BL>>RShift) & byteMask)/255.0f), 2.2f);
                        G += Math.pow((((BL>>GShift) & byteMask)/255.0f), 2.2f);
                        B += Math.pow((((BL>>BShift) & byteMask)/255.0f), 2.2f); 
                        A = (((BL>>AShift) & byteMask) > A ? ((BL>>AShift) & byteMask): A); n++;
                    }
                    if(((BR>>AShift) & byteMask)>0){
                        R += Math.pow((((BR>>RShift) & byteMask)/255.0f), 2.2f);
                        G += Math.pow((((BR>>GShift) & byteMask)/255.0f), 2.2f);
                        B += Math.pow((((BR>>BShift) & byteMask)/255.0f), 2.2f);
                        A = (((BR>>AShift) & byteMask) > A ? ((BR>>AShift) & byteMask): A); n++;
                    }
                    if(n==0 || A==0){levels[i].setRGB(x, y, new Color(255, 255, 255, 0).getRGB());}
                    else{

                        RF = (int)(255*(float)Math.pow(R/n, 1/2.2f)+0.5f); 
                        GF = (int)(255*(float)Math.pow(G/n, 1/2.2f)+0.5f); 
                        BF = (int)(255*(float)Math.pow(B/n, 1/2.2f)+0.5f);
                        RF = (RF<=0 ? 0 : (RF>=255 ? 255 : RF)); BF = (BF<=0 ? 0 : (BF>=255 ? 255 : BF)); GF = (GF<=0 ? 0 : (GF>=255 ? 255 : GF));

                        levels[i].setRGB(x, y, (RF<<RShift) + (GF<<GShift) + (BF<<BShift) + (A<<AShift));
                    }

                }
            }
            xMax>>=1; yMax>>=1;
        }
        xMax = xBound>>1; yMax = yBound >> 1;
        for(int i = 1; i < mipMapCount; i++){
            for(int x = 0; x < xMax; x++){
                for(int y=0; y < yMax; y++){
                    if(((levels[i].getRGB(x, y)>>AShift) & byteMask) == 0){
                        int c = levels[mipMapCount].getRGB(x>>(mipMapCount-i), y>>(mipMapCount-i));
                        c &= ~(byteMask<<AShift);
                        levels[i].setRGB(x, y, c);
                    }
                }
            }
            xMax>>=1; yMax>>=1;
        }

        for(int i = 0; i <= mipMapCount; i++){
            try{ImageIO.write(levels[i], "png", outMaps[i]);}
            catch(IOException e){e.printStackTrace(); break;}
        }
    }
}