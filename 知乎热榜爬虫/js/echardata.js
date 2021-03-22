var myChart = echarts.init(document.getElementById('main'));
var option = {
    title: {
        text: '知乎热榜统计数据'
    },
    tooltip: {},
    legend: {
        data: ['出现次数']
    },
    xAxis: {
        data: Xlist
    },
    yAxis: {},
    series: [{
        name: '热度',
        type: 'bar',
        data: Ylist
    }]
};

// 使用刚指定的配置项和数据显示图表。
myChart.setOption(option);