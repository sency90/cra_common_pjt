#pragma once

class PageEnum {
public:
    enum Enum {
        None,
        eCarTypePage,
        eEnginePage,
        eBrakePage,
        eSteeringPage,
        eRunOrTestPage,
        Count
    };

    void MoveToPrevPage() {
        if(IsStartPage()) return; //do nothing

        int page_no = static_cast<int>(cur_page);
        page_no--;
        cur_page = static_cast<PageEnum::Enum>(page_no);
    }

    void MoveToNextPage() {
        if(IsEndPage()) return; //do nothing

        int page_no = static_cast<int>(cur_page);
        page_no++;
        cur_page = static_cast<PageEnum::Enum>(page_no);
    }

    static PageEnum GetStartPage() {
        return eCarTypePage;
    }

    void MoveToStartPage() {
        cur_page = GetStartPage().Get();
    }

    bool IsStartPage() const {
        return cur_page == eCarTypePage;
    }

    bool IsEndPage() const {
        return cur_page == eRunOrTestPage;
    }

    bool operator==(const PageEnum &rhs) const {
        return cur_page == rhs.cur_page;
    }

    bool operator==(const PageEnum::Enum & rhs) const {
        return cur_page == rhs;
    }

    PageEnum():cur_page(None) {}
    PageEnum(PageEnum &page):cur_page(page.cur_page) {}
    PageEnum(const PageEnum &page):cur_page(page.cur_page) {}
    PageEnum(PageEnum::Enum cur_page):cur_page(cur_page) {}

    Enum Get() const { return cur_page; }

private:
    Enum cur_page;
};
