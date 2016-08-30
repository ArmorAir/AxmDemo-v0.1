#pragma once





// desktop分三类窗口拖动方式:
// 1. 保持比例，两侧黑色填充（缩放）...多数用于在desktop端模拟调试mobile端效果
// 2. 全图渲染，viewRatio不变（不缩放）
// 3. 全图渲染，viewRatio随窗口大小变化而变化（缩放）

// desktop窗口拖动自动调整:
// 1. 拖动后对大小判断并重新自调整（例如保持指定宽高比）