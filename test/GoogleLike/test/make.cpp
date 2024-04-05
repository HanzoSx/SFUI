#include <iostream>
#include <algorithm>
#include <fstream>
#include <codecvt>

// #include <windows.h>

#include <SFUI.hpp>
#include <GoogleLikeButton.hpp>

#define INT_MAX 1000000000

std::vector<std::string> EnchantingName_en;
std::vector<std::string> EnchantingName_zh;

struct Item
{
    std::string name;
    std::vector<int> EnchantingLevel;
};

std::string GenerateInstructions(Item item)
{
    std::string command = "/give @p "+item.name+"{";
    std::string Enchantment = "Enchantments:[";
    int m=EnchantingName_en.size();
    for(int i=0;i<m;i++){
        if(item.EnchantingLevel[i]!=0){
            Enchantment+="{id:"+EnchantingName_en[i]+",lvl:"+std::to_string(item.EnchantingLevel[i])+"s},";
        }
    }
    Enchantment=Enchantment.substr(0,Enchantment.length()-1);
    Enchantment+="]";
    //string display;
    command+=Enchantment+"}";
    return command;
}

bool SetClipboardText(const std::wstring& text) {
    // // 打开剪贴板
    // if (!OpenClipboard(nullptr)) {
    //     std::cerr << "Failed to open the clipboard." << std::endl;
    //     return false;
    // }

    // // 清空剪贴板
    // if (!EmptyClipboard()) {
    //     std::cerr << "Failed to empty the clipboard." << std::endl;
    //     CloseClipboard();
    //     return false;
    // }

    // // 分配内存
    // HGLOBAL hClipboardData = GlobalAlloc(GMEM_MOVEABLE, (text.length() + 1) * sizeof(wchar_t));
    // if (hClipboardData == nullptr) {
    //     std::cerr << "Failed to allocate memory." << std::endl;
    //     CloseClipboard();
    //     return false;
    // }

    // // 锁定内存并复制数据
    // wchar_t* pszText = static_cast<wchar_t*>(GlobalLock(hClipboardData));
    // if (pszText == nullptr) {
    //     std::cerr << "Failed to lock memory." << std::endl;
    //     CloseClipboard();
    //     GlobalFree(hClipboardData);
    //     return false;
    // }
    // wcscpy_s(pszText, text.length() + 1, text.c_str());

    // // 释放内存并解锁
    // GlobalUnlock(hClipboardData);

    // // 设置剪贴板数据
    // if (SetClipboardData(CF_UNICODETEXT, hClipboardData) == nullptr) {
    //     std::cerr << "Failed to set clipboard data." << std::endl;
    //     CloseClipboard();
    //     GlobalFree(hClipboardData);
    //     return false;
    // }

    // // 关闭剪贴板
    // CloseClipboard();

    return true;
}

class Target
{
public:

    sfu::GoogleLikeButton button;
    std::string name;

    Target() : button(m_sprite, 50, 0) {}

    void addTexture(std::string path)
    {
        m_texture.push_back(sf::Texture());
        m_texture.back().loadFromFile(path);

        if (m_texture.size() == 1) setTexture(0);
    }

    void setTexture(size_t index)
    {
        m_sprite.setTexture(m_texture.at(index));
        float scale = std::min(
            (button.getRadius() * 2 + button.getWidth()) * 0.65
                / m_texture.at(index).getSize().x,
            (button.getRadius() * 2) * 0.65
                / m_texture.at(index).getSize().y
        );
        m_sprite.setScale(scale, scale);
        m_sprite.setOrigin(
            m_sprite.getLocalBounds().width / 2,
            m_sprite.getLocalBounds().height / 2
        );
        m_sprite.setPosition(
            button.getRadius() + button.getWidth() / 2,
            button.getRadius()
        );
    }

private:
    
    std::vector<sf::Texture> m_texture;
    sf::Sprite m_sprite;

};

std::string lower(std::string str)
{
    for (auto& it : str)
        it = std::tolower(it);
    return str;
}

void init()
{
    std::ifstream file;
    file.open("data.csv");

    std::string en, zh;
    while (file >> en)
    {
        file >> zh;// std::wcout << std::wstring(sf::String(zh));
        EnchantingName_en.push_back(en);
        EnchantingName_zh.push_back(zh);
    }
    file.close();
}


int main()
{
sf::Clock clock;
clock.restart();
    sf::Texture t;
    for (int i = 1; i <= 55; ++ i)
        t.loadFromFile("test/./icon (" + std::to_string(i) + ").png");

std::cout << clock.restart().asSeconds() << " s\n";

    sfu::Window UIwindow;
    UIwindow.creat(sf::VideoMode(1600, 800), "Netease MC = false");
    sf::RenderWindow &window = UIwindow.getWindow();

    init();

    std::vector<std::string> materialName = {"Leather_Wood", "Chainmail_Stone", "Iron_Ingot", "Gold_Ingot", "Diamond", "Netherite_Ingot"};
    Target materialButton[6];
    for (size_t index = 0; index < materialName.size(); ++ index)
    {
        UIwindow.push_back(materialButton[index].button);
        materialButton[index].button.setViewPosition(sf::Vector2f(20, index * 100 + 100));
        materialButton[index].addTexture("./icon/Material/" + materialName[index] + ".png");
    }

///////////////////////////////////////////////////////////

    std::vector<std::string> toolMaterial = {"Wooden", "Stone", "Iron", "Golden", "Diamond", "Netherite"};
    std::vector<std::string> armorMaterial = {"Leather", "Chainmail", "Iron", "Golden", "Diamond", "Netherite"};
    std::vector<std::string> itemName = {
        "Helmet", "Chestplate", "Leggings", "Boots",
        "Axe", "Pickaxe", "Shovel", "Sword"
    };

    Target itemsButton[8];
    for (size_t index = 0; index < 8; ++ index)
    {
        UIwindow.push_back(itemsButton[index].button);
        itemsButton[index].button.setViewPosition(
            index < 4 ?
                sf::Vector2f(120, 180 + index * 100) :
                sf::Vector2f(120 + 120 + index % 2 * 100, index / 2 * 100)
        );

        if (index < 4)
        {
            for (auto it : armorMaterial)
            {
                itemsButton[index].addTexture("./icon/" + itemName[index] + "/" + it + "_" + itemName[index] + ".png");
                itemsButton[index].name = lower(it) + "_" + lower(itemName[index]);
            }
            itemsButton[index].setTexture(5);
        }
        else
        {
            for (auto it : toolMaterial)
            {
                itemsButton[index].addTexture("./icon/" + itemName[index] + "/" + it + "_" + itemName[index] + ".png");
                itemsButton[index].name = lower(it) + "_" + lower(itemName[index]);
            }
            itemsButton[index].setTexture(5);
        }
    }

    size_t material = 5, item = 4;
    materialButton[5].button.Select();
    itemsButton[4].button.Select();

std::cout << "Material/Item Button load for " << clock.restart().asSeconds() << " s\n";
///////////////////////////////////////////////////////////

    sf::Font font;
    std::cout << "load font : " << font.loadFromFile("DENG.TTF") << "\n";

    sf::Text addText, delText;
    addText.setFont(font);
    delText.setFont(font);

    unsigned int ChSize = 25;
    addText.setCharacterSize(ChSize);
    delText.setCharacterSize(ChSize);

    addText.setFillColor(sf::Color::White);
    delText.setFillColor(sf::Color::White);
    float OutlineT = 1.f;
    addText.setOutlineThickness(OutlineT);
    delText.setOutlineThickness(OutlineT);
    addText.setOutlineColor(sf::Color::Black);
    delText.setOutlineColor(sf::Color::Black);

    addText.setString("+");
    delText.setString("-");

    addText.setOrigin(addText.getLocalBounds().width / 2, addText.getLocalBounds().height / 2);
    delText.setOrigin(delText.getLocalBounds().width / 2, delText.getLocalBounds().height / 2);

    addText.setPosition(15, 6);
    delText.setPosition(14, 0);

    Item Item;
    for (auto it : EnchantingName_en) Item.EnchantingLevel.push_back(0);

    std::vector<sf::Text> ENameText, LevelText;
    std::vector<sfu::GoogleLikeButton> addButton, delButton;
    addButton.reserve(EnchantingName_en.size());
    delButton.reserve(EnchantingName_en.size());

// std::cout << "      set a/d Text : " << clock.getElapsedTime().asSeconds() << " s\n";
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    for (size_t index = 0; index < EnchantingName_en.size(); ++ index)
    {
        sf::Text tmpEName, tmplevel;
        tmpEName.setFont(font);
        tmplevel.setFont(font);

        tmpEName.setCharacterSize(ChSize);
        tmplevel.setCharacterSize(ChSize);

        tmpEName.setFillColor(sf::Color::Black);
        tmplevel.setFillColor(sf::Color::Black);


        tmpEName.setString(converter.from_bytes(EnchantingName_zh[index]));// std::cout << EnchantingName_zh[index];
        tmplevel.setString(std::to_string(0 & INT_MAX - 1));

        tmpEName.setPosition(500 + index % 3 * 360, 50 + index / 3 * 40);
        tmplevel.setPosition(630 + index % 3 * 360, 50 + index / 3 * 40);

        ENameText.push_back(tmpEName);
        LevelText.push_back(tmplevel);

// sf::Time t = clock.getElapsedTime();
        addButton.emplace_back(addText, 15, 0);
        delButton.emplace_back(delText, 15, 0);
// std::cout << "      emplace_back[" << index << "] : " << (clock.getElapsedTime() - t).asSeconds() << " s\n";
    }
// std::cout << "      setEnText : " << clock.getElapsedTime().asSeconds() << " s\n";
    for (auto& it : addButton)
    {
        static size_t index = 0;
        UIwindow.push_back(it);
        it.setViewPosition(sf::Vector2f(780 + index % 3 * 360, 50 + index / 3 * 40));
        ++ index;
    }

    for (auto& it : delButton)
    {
        static size_t index = 0;
        UIwindow.push_back(it);
        it.setViewPosition(sf::Vector2f(812 + index % 3 * 360, 50 + index / 3 * 40));
        ++ index;
    }

std::cout << "list Button load for " << clock.restart().asSeconds() << " s\n";
///////////////////////////////////////////////////////////

    sf::Text command;
    command.setFont(font);
    command.setCharacterSize(ChSize);
    command.setFillColor(sf::Color::Black);
    command.setPosition(240, 715);

///////////////////////////////////////////////////////////

    Target copyButton;
    copyButton.addTexture("./icon/copy.png");
    copyButton.button.setViewPosition(sf::Vector2f(120, 680));
    UIwindow.push_back(copyButton.button);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::EventType::Closed:
                    window.close();
                    break;
                
                default:
                    break;
            }
            UIwindow.handleEvent(event);

            for (size_t index = 0; index < 6; ++ index)
                if (materialButton[index].button.isPressed(sf::Mouse::Left))
                {
                    materialButton[material].button.Unselect();
                    materialButton[index].button.Select();
                    material = index;
                    for (size_t i = 0; i < 8; ++ i) itemsButton[i].setTexture(material);
                }

            for (size_t index = 0; index < 8; ++ index)
                if (itemsButton[index].button.isPressed(sf::Mouse::Left))
                {
                    itemsButton[item].button.Unselect();
                    itemsButton[index].button.Select();
                    item = index;
                }

            for (size_t index = 0; index < addButton.size(); ++ index)
            {
                if (addButton[index].isPressed(sf::Mouse::Left))
                    Item.EnchantingLevel[index] = std::min(1LL + Item.EnchantingLevel[index], -1LL + INT_MAX);
                if (addButton[index].isPressed(sf::Mouse::Right))
                    Item.EnchantingLevel[index] = std::min(10LL * Item.EnchantingLevel[index], -1LL + INT_MAX);
                LevelText[index].setString(std::to_string(Item.EnchantingLevel[index]));
            }
            for (size_t index = 0; index < delButton.size(); ++ index)
            {
                if (delButton[index].isPressed(sf::Mouse::Left))
                    Item.EnchantingLevel[index] = std::max(Item.EnchantingLevel[index] - 1, 1 - 1);
                if (delButton[index].isPressed(sf::Mouse::Right))
                    Item.EnchantingLevel[index] = std::max(Item.EnchantingLevel[index] / 10, 1 - 1);
                LevelText[index].setString(std::to_string(Item.EnchantingLevel[index]));
            }

            if (copyButton.button.isPressed(sf::Mouse::Left)) SetClipboardText(command.getString());
        }
        
        window.clear(sf::Color::White);
        window.draw(UIwindow);

        sf::View view;
        view.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
        window.setView(view);
        for (auto it : ENameText) window.draw(it);
        for (auto it : LevelText) window.draw(it);
        
        if (item < 4)
            Item.name = lower(armorMaterial[material]) + "_" + lower(itemName[item]);
        else
            Item.name = lower(toolMaterial[material]) + "_" + lower(itemName[item]);
                
        command.setString(GenerateInstructions(Item));
        window.draw(command);

        window.display();

        sf::sleep(sf::milliseconds(10));
    }
    

    return 0;

sizeof(sfu::NestView);// 28
sizeof(sfu::Control);// 88
sizeof(sfu::Button);// 120
sizeof(sfu::GoogleLikeButton);// 1192
    sizeof(sfu::CircleFan);// 292
    sizeof(sf::RectangleShape);// 284
    sizeof(DynamicParameter);// 40

    sizeof(int);
    
}