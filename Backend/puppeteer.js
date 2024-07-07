const puppeteer = require('puppeteer');

async function image(content) {
    const browser = await puppeteer.launch();

    const page = await browser.newPage();
    await page.setContent(content, { waitUntil: 'networkidle0' });
    const selector = '#sop div div:nth-child(6) div';
    await page.waitForSelector(selector);
    const element = await page.$(selector);
    const boundingbox = await element.boundingBox();
    await element.screenshot({
        path: './build/logic-circuit.png', clip: {
            x: -10,
            y: -15,
            width: boundingbox.width,
            height: boundingbox.height
        }
    });
    await browser.close();
};

module.exports = image;