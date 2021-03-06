//
//  TextureManager.cpp
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/22/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include "TextureManager.h"
#include "Camera.h"

typedef map<string, SDL_Texture*>::iterator textureMapIterator;
TextureManager* TextureManager::s_pInstance = 0;

TextureManager::TextureManager(){
    //Private unused ctor
}

TextureManager::~TextureManager(){
    cout << "Deleting texture manager\n";
    //m_textureMap.clear();
}

bool TextureManager::load(string fileName, string id,
                          SDL_Renderer* pRenderer){
    if (!doesTextureExist(id)){
        SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

        
        if (pTempSurface == 0){
            cout << "ERROR - Could not load " << fileName.c_str() << "\n";
            return false;
        } else {
            cout << "Loaded Texture: " << fileName.c_str() << "\n";
        }


        
        SDL_Texture* pTexture =
        SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
        
        SDL_FreeSurface(pTempSurface);
        
        //If everything went okay store texture in map
        if (pTexture != 0){
            cout << "Image load success\n";
            m_textureMap[id] = pTexture;
            return true;
        }
        
        //if we fall through it failed
        cout << "Image load fell through, fail\n";
    }
    return false;
}



void TextureManager::drawFrame(GameObjectParams* params,
                               SDL_Renderer* pRenderer,
                               SDL_RendererFlip flip , double zoom){
    if (doesTextureExist(params->getTextureID())){
        //Set camera offset if scrolling
        SDL_Rect cameraOffset;
        cameraOffset.x = 0;
        cameraOffset.y = 0;
        
        if (params->isScrolling()){
            cameraOffset.x = Camera::Instance()->getPosition().getX();
            cameraOffset.y = Camera::Instance()->getPosition().getY();
        }
        
        //Configure source and destination Rects
        SDL_Rect srcRect;
        SDL_Rect dstRect;
        
        srcRect.x = params->getSourceWidth() * params->getFrame();
        srcRect.y = params->getSourceHeight() * (params->getRow() - 1);
        srcRect.w = dstRect.w = params->getSourceWidth();
        srcRect.h = dstRect.h = params->getSourceHeight();
        
        dstRect.w = params->getWidth() * zoom;
        dstRect.h = params->getHeight() * zoom;
        dstRect.x = ((params->getX()) -cameraOffset.x) *  zoom;
        dstRect.y = ((params->getY()) -cameraOffset.y) * zoom;
        
        
        //Apply Blend modes
        SDL_BlendMode oldBlendMode;
        SDL_Color oldColor;
        
        SDL_GetTextureAlphaMod(m_textureMap[params->getTextureID()], &oldColor.a);
        SDL_GetTextureColorMod(m_textureMap[params->getTextureID()], &oldColor.r, &oldColor.g, &oldColor.b);
        SDL_GetTextureBlendMode(m_textureMap[params->getTextureID()], &oldBlendMode);
        
        SDL_SetTextureBlendMode(m_textureMap[params->getTextureID()], params->getBlendMode());
        SDL_SetTextureAlphaMod(m_textureMap[params->getTextureID()], params->getColor().a);
        SDL_SetTextureColorMod(m_textureMap[params->getTextureID()],
                               params->getColor().r, params->getColor().g,
                               params->getColor().b);
        
        SDL_RenderCopyEx(pRenderer, m_textureMap[params->getTextureID()],
                         &srcRect, &dstRect, params->getAngle(), 0, flip);
        
        //Reset Blend Modes
        SDL_SetTextureAlphaMod(m_textureMap[params->getTextureID()], oldColor.a);
        SDL_SetTextureBlendMode(m_textureMap[params->getTextureID()], oldBlendMode);
        SDL_SetTextureColorMod(m_textureMap[params->getTextureID()],
                               oldColor.r, oldColor.g,
                               oldColor.b);
    }
    
}


void TextureManager::drawTile(string id, int margin, int spacing, double x,
                              double y, int width, int height, int currentRow,
                              int currentFrame,double zoom, SDL_Renderer *pRenderer){
    
    if (doesTextureExist(id)){
        SDL_Rect cameraOffset;
        cameraOffset.x = 0;
        cameraOffset.y = 0;
        
        cameraOffset.x = Camera::Instance()->getPosition().getX();
        cameraOffset.y = Camera::Instance()->getPosition().getY();
        
        SDL_Rect srcRect;
        SDL_Rect destRect;
        srcRect.x = margin + (spacing + width) * currentFrame;
        srcRect.y = margin + (spacing + height) * currentRow;
        srcRect.w = destRect.w = width;
        srcRect.h = destRect.h = height;
        
        destRect.h = height * zoom;
        destRect.w = width * zoom;
        destRect.x = (x - cameraOffset.x) * zoom;
        destRect.y = (y - cameraOffset.y) * zoom;
        
        
        SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect,
                         0, 0, SDL_FLIP_NONE);
    }
}

void TextureManager::clean(){
    m_textureMap.clear();
    
    delete s_pInstance;
}

void TextureManager::clearFromTextureMap(string id){
    m_textureMap.erase(id);
}

TextureManager* TextureManager::Instance(){
    if (s_pInstance == 0){
        s_pInstance = new TextureManager();
    }
    return s_pInstance;
}


bool TextureManager::doesTextureExist(string id){
    if (m_textureMap[id]){
        return true;
    }
    return false;
}










/*
 *********************
 Deprecated
 *********************
*/

//void TextureManager::drawFrame(string id, Vector2D<double> pos,
//                               int width, int height,
//                               int currentRow, int currentFrame,
//                               SDL_Renderer* pRenderer, SDL_RendererFlip flip){
//    if (doesTextureExist(id)){
//        SDL_Rect srcRect;
//        SDL_Rect dstRect;
//
//        srcRect.x = width * currentFrame;
//        srcRect.y = height * (currentRow - 1);
//        srcRect.w = dstRect.w = width;
//        srcRect.h = dstRect.h = height;
//
//        dstRect.w = width;
//        dstRect.h = height;
//        dstRect.x = pos.getX();
//        dstRect.y = pos.getY();
//        SDL_RenderCopyEx(pRenderer, m_textureMap[id],
//                         &srcRect, &dstRect, 0.0, 0, flip);
//    }
//
//}


//void TextureManager::draw(string id, double x, double y,
//                          int width, int height,
//                          SDL_Renderer* pRenderer, SDL_RendererFlip flip){
//    if (doesTextureExist(id)){
//        SDL_Rect srcRect;
//        SDL_Rect dstRect;
//
//        srcRect.x = 0;
//        srcRect.y = 0;
//        srcRect.w = dstRect.w = width;
//        srcRect.h = dstRect.h = height;
//        dstRect.x = x;
//        dstRect.y = y;
//
//        SDL_RenderCopyEx(pRenderer, m_textureMap[id],
//                         &srcRect, &dstRect, 0.0, 0, flip);
//    }
//}

//void TextureManager::draw(string id, Vector2D<double> pos,
//                          int width, int height,
//                          SDL_Renderer* pRenderer, SDL_RendererFlip flip){
//    if (doesTextureExist(id)){
//        SDL_Rect srcRect;
//        SDL_Rect dstRect;
//
//        srcRect.x = 0;
//        srcRect.y = 0;
//        srcRect.w = dstRect.w = width;
//        srcRect.h = dstRect.h = height;
//        dstRect.x = pos.getX();
//        dstRect.y = pos.getY();
//
//        SDL_RenderCopyEx(pRenderer, m_textureMap[id],
//                         &srcRect, &dstRect, 0.0, 0, flip);
//    }
//}


//void TextureManager::drawFrame(string id, double x, double y,
//                               int width, int height,
//                               int currentRow, int currentFrame,double zoom,
//                               SDL_Renderer* pRenderer, SDL_RendererFlip flip){
//    if (doesTextureExist(id)){
//        SDL_Rect srcRect;
//        SDL_Rect dstRect;
//
//        srcRect.x = width * currentFrame;
//        srcRect.y = height * (currentRow - 1);
//        srcRect.w = dstRect.w = width;
//        srcRect.h = dstRect.h = height;
//
//        dstRect.w = width * zoom;
//        dstRect.h = height * zoom;
//        dstRect.x = (x * zoom);
//        dstRect.y = (y * zoom);
//
//
//        SDL_RenderCopyEx(pRenderer, m_textureMap[id],
//                         &srcRect, &dstRect, 0.0, 0, flip);
//    }
//
//}











//END


