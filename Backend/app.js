const express = require('express');
const app = express();
const axios = require('axios');
const cheerio = require('cheerio');
const image = require('./puppeteer');

app.use(express.json());
app.use(express.urlencoded({ extended: true }));

app.listen(3000, () => {
    console.log(`Server is running on port 3000`);
});

app.post('/solve2var', async (req, res) => {
    const formData = {
        calctype: 'sop',
        in0: '0',
        in1: '0',
        in2: '0',
        in3: '0',
        drawtype: 'htmlcss'
    };
    const { minterms } = req.body;
    for (let i = 0; i < 4; i++) {
        if (minterms.includes(i.toString())) {
            formData[`in${i}`] = '1';
        }
    }
    const response = await axios.post('http://www.32x8.com/circuits2', formData, {
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
        }
    });
    const $ = cheerio.load(response.data);
    const cssUrl = $('link').attr().href;
    const css = await axios.get('http://www.32x8.com/' + cssUrl);
    const style = `<style>${css.data}</style>`;
    $('head').append(style);
    image($('html').html());
    res.send($('html').html());
});

app.post('/solve3var', async (req, res) => {
    const formData = {
        calctype: 'sop',
        in0: '0',
        in1: '0',
        in2: '0',
        in3: '0',
        drawtype: 'htmlcss',
        in4: '0',
        in5: '0',
        in6: '0',
        in7: '0'

    };
    const { minterms } = req.body;
    for (let i = 0; i < 8; i++) {
        if (minterms.includes(i.toString())) {
            formData[`in${i}`] = '1';
        }
    }
    const response = await axios.post('http://www.32x8.com/circuits3', formData, {
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
        }
    });
    const $ = cheerio.load(response.data);
    const cssUrl = $('link').attr().href;
    const css = await axios.get('http://www.32x8.com/' + cssUrl);
    const style = `<style>${css.data}</style>`;
    $('head').append(style);
    image($('html').html());
    res.send($('html').html());
});

app.post('/solve4var', async (req, res) => {
    const formData = {
        calctype: 'sop',
        in0: '0',
        in1: '0',
        in2: '0',
        in3: '0',
        drawtype: 'htmlcss',
        in4: '0',
        in5: '0',
        in6: '0',
        in7: '0',
        in8: '0',
        in9: '0',
        in10: '0',
        in11: '0',
        in12: '0',
        in13: '0',
        in14: '0',
        in15: '0'
    };
    const { minterms } = req.body;
    for (let i = 0; i < 16; i++) {
        if (minterms.includes(i.toString())) {
            formData[`in${i}`] = '1';
        }
    }
    const response = await axios.post('http://www.32x8.com/circuits4', formData, {
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
        }
    });
    const $ = cheerio.load(response.data);
    const cssUrl = $('link').attr().href;
    const css = await axios.get('http://www.32x8.com/' + cssUrl);
    const style = `<style>${css.data}</style>`;
    $('head').append(style);
    image($('html').html());
    res.send($('html').html());
});

app.post('/solve5var', async (req, res) => {
    const formData = {
        calctype: 'sop',
        in0: '0',
        in1: '0',
        in2: '0',
        in3: '0',
        drawtype: 'htmlcss',
        in4: '0',
        in5: '0',
        in6: '0',
        in7: '0',
        in8: '0',
        in9: '0',
        in10: '0',
        in11: '0',
        in12: '0',
        in13: '0',
        in14: '0',
        in15: '0',
        in16: '0',
        in17: '0',
        in18: '0',
        in19: '0',
        in20: '0',
        in21: '0',
        in22: '0',
        in23: '0',
        in24: '0',
        in25: '0',
        in26: '0',
        in27: '0',
        in28: '0',
        in29: '0',
        in30: '0',
        in31: '0'
    };
    const { minterms } = req.body;
    for (let i = 0; i < 32; i++) {
        if (minterms.includes(i.toString())) {
            formData[`in${i}`] = '1';
        }
    }
    const response = await axios.post('http://www.32x8.com/circuits5', formData, {
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
        }
    });
    const $ = cheerio.load(response.data);
    const cssUrl = $('link').attr().href;
    const css = await axios.get('http://www.32x8.com/' + cssUrl);
    const style = `<style>${css.data}</style>`;
    $('head').append(style);
    image($('html').html());
    res.send($('html').html());
})
