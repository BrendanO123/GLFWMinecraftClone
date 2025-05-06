import java.io.*;
import javax.imageio.*;
import java.awt.image.*;
import java.awt.*;
import java.util.*;

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

                    int R, B, G, A; R = G = B = A = 0; int n = 0;

                    if(((TL>>AShift) & byteMask)>0){
                        R += ((TL>>RShift) & byteMask);// * ((TL>>AShift) & byteMask)/255; 
                        G += ((TL>>GShift) & byteMask);// * ((TL>>AShift) & byteMask)/255; 
                        B += ((TL>>BShift) & byteMask);// * ((TL>>AShift) & byteMask)/255; 
                        A = (((TL>>AShift) & byteMask) > A ? ((TL>>AShift) & byteMask): A); n++;
                    }
                    if(((TR>>AShift) & byteMask)>0){
                        R += ((TR>>RShift) & byteMask);// * ((TR>>AShift) & byteMask)/255; 
                        G += ((TR>>GShift) & byteMask);// * ((TR>>AShift) & byteMask)/255; 
                        B += ((TR>>BShift) & byteMask);// * ((TR>>AShift) & byteMask)/255; 
                        A = (((TR>>AShift) & byteMask) > A ? ((TR>>AShift) & byteMask): A); n++;
                    }
                    if(((BL>>AShift) & byteMask)>0){
                        R += ((BL>>RShift) & byteMask);// * ((BL>>AShift) & byteMask)/255; 
                        G += ((BL>>GShift) & byteMask);// * ((BL>>AShift) & byteMask)/255; 
                        B += ((BL>>BShift) & byteMask);// * ((BL>>AShift) & byteMask)/255; 
                        A = (((BL>>AShift) & byteMask) > A ? ((BL>>AShift) & byteMask): A); n++;
                    }
                    if(((BR>>AShift) & byteMask)>0){
                        R += ((BR>>RShift) & byteMask);// * ((BR>>AShift) & byteMask)/255; 
                        G += ((BR>>GShift) & byteMask);// * ((BR>>AShift) & byteMask)/255; 
                        B += ((BR>>BShift) & byteMask);// * ((BR>>AShift) & byteMask)/255; 
                        A = (((BR>>AShift) & byteMask) > A ? ((BR>>AShift) & byteMask): A); n++;
                    }
                    if(n==0 || A==0){levels[i].setRGB(x, y, new Color(255, 255, 255, 0).getRGB());}
                    else{

                        R = (int)((R/((float)n))+0.5f); B = (int)((B/((float)n))+0.5f); G = (int)((G/((float)n))+0.5f);
                        R = (R<=0 ? 0 : (R>=255 ? 255 : R)); B = (B<=0 ? 0 : (B>=255 ? 255 : B)); G = (G<=0 ? 0 : (G>=255 ? 255 : G));

                        levels[i].setRGB(x, y, (R<<RShift) + (G<<GShift) + (B<<BShift) + (A<<AShift));
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